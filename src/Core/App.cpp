#include "App.h"
#include <Core/Modules/CommunicationModule.h>
#include <Core/Modules/GPIOModule.h>
#include <Core/Modules/TelegramBotModule.h>
#include <Core/Modules/MessageGeneratorModule.h>
#include <Core/Communication/Message.h>
#include <Gpio/GpioManager.h>
#include <thread>
#include <iostream>
#include <csignal>
#include <fstream>
#include <functional>

using namespace core;

App &App::getInstance() noexcept
{
    static App app;
    return app;
}

App::App() noexcept
    : m_gpioManager(std::make_shared<GPIO::GpioManager>())
    , m_moduleNames{GPIOModule::k_moduleName, TelegramBotModule::k_moduleName, MessageGeneratorModule::k_moduleName}
{
    signal(SIGINT, App::signalHandler);
}

App::~App() noexcept = default;

bool App::init() noexcept
{
    // Build modules
    auto communicationModule = std::make_unique<CommunicationModule>();
    auto &communicationQueue = communicationModule->getInputQueue();

    if (!loadModules("config.json", communicationQueue)) {
        return false;
    }

    // Setup message dispatcher
    communicationModule->setup(m_modules);

    m_modules.push_back(std::move(communicationModule));
    for (auto &module : m_modules) {
        if (!module->init()) {
            return false;
        }
    }
    std::cout << "App init" << std::endl;
    return true;
}

void App::start() noexcept
{
    std::vector<std::thread> threads;
    threads.reserve(m_modules.size() - 1);
    // Start modules
    for (size_t i = 0; i < m_modules.size() - 1; ++i) {
        threads.emplace_back(&BaseModule::start, m_modules[i].get());
    }
    // Last module (communication) is run in the main thread
    m_modules[m_modules.size() - 1]->start();

    for (auto &thread : threads) {
        thread.join();
    }

    std::cout << "App closing" << std::endl;
}

void App::exit() noexcept
{
    auto exitMessage = std::make_shared<Message>(MessageType::EXIT);
    for (auto &module : m_modules) {
        module->getInputQueue()->push(exitMessage);
    }
}

bool App::loadModules(const std::string &configFilePath,
                      std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> &communicationQueue) noexcept
{
    nlohmann::json configFile;
    try {
        std::unordered_map<std::string, std::function<std::unique_ptr<BaseModule>(const nlohmann::json &json)>>
            builderMap = {{GPIOModule::k_moduleName,
                           std::function<std::unique_ptr<BaseModule>(const nlohmann::json &json)>(
                               [&](const nlohmann::json &json) {
                                   return std::make_unique<GPIOModule>(m_gpioManager, communicationQueue, json);
                               })},
                          {TelegramBotModule::k_moduleName,
                           std::function<std::unique_ptr<BaseModule>(const nlohmann::json &json)>(
                               [&](const nlohmann::json &json) {
                                   return std::make_unique<TelegramBotModule>(communicationQueue, json);
                               })},
                          {MessageGeneratorModule::k_moduleName,
                           std::function<std::unique_ptr<BaseModule>(const nlohmann::json &json)>(
                               [&](const nlohmann::json &json) {
                                   return std::make_unique<MessageGeneratorModule>(communicationQueue, json);
                               })}};
        std::ifstream configStream(configFilePath);
        configStream >> configFile;
        for (const auto &moduleName : m_moduleNames) {
            if (const auto it = configFile.find(moduleName); it != configFile.end()) {
                if (auto builderMapIt = builderMap.find(moduleName); builderMapIt != builderMap.end()) {
                    m_modules.emplace_back(builderMapIt->second(*it));
                }
            }
        }
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Error creating the modules: " << e.what() << "\n";
        return false;
    }
}

void App::signalHandler(int /*signal*/)
{
    std::cout << "Signal captured, exiting application" << std::endl;
    App::getInstance().exit();
}
