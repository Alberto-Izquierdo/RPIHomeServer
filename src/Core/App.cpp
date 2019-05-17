#include "App.h"
#include <Core/Modules/CommunicationModule.h>
#include <Core/Modules/GPIOModule.h>
#include <Core/Modules/TelegramBotModule.h>
#include <Core/Communication/Message.h>
#include <Gpio/GpioManager.h>
#include <thread>
#include <iostream>
#include <signal.h>
#include <fstream>

using namespace core;

App &App::getInstance()
{
    static App app;
    return app;
}

App::App() noexcept
    : m_gpioManager(std::make_shared<GPIO::GpioManager>())
    , m_moduleNames({GPIOModule::k_moduleName, TelegramBotModule::k_moduleName})
{
    signal(SIGINT, App::signalHandler);
}

App::~App() noexcept
{
}

bool App::init() noexcept
{
    // Build modules
    auto communicationModule(new CommunicationModule());
    auto &communicationQueue = communicationModule->getInputQueue();

    loadModules("config.json", communicationQueue);

    // Setup message dispatcher
    communicationModule->setup(m_modules);

    m_modules.emplace_back(std::move(communicationModule));
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
    threads.reserve(m_modules.size());
    // Start modules
    for (auto &module : m_modules) {
        threads.emplace_back(&BaseModule::start, module.get());
    }
    std::cout << "Modules started" << std::endl;
    for (auto &thread : threads) {
        thread.join();
    }
    std::cout << "App closing" << std::endl;
}

void App::exit() noexcept
{
    for (auto &module : m_modules) {
        if (module->getType() == BaseModule::Type::COMMUNICATION) {
            auto exitMessage = std::make_shared<Message>(MessageType::EXIT);
            module->getInputQueue()->push(exitMessage);
            return;
        }
    }
}

void App::loadModules(const std::string &configFilePath,
                      std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> &communicationQueue) noexcept
{
    nlohmann::json configFile;
    std::ifstream configStream(configFilePath);
    configStream >> configFile;
    for (const auto &moduleName : m_moduleNames) {
        const auto it = configFile.find(moduleName);
        if (it != configFile.end()) {
            if (moduleName == GPIOModule::k_moduleName) {
                m_modules.emplace_back(new GPIOModule(m_gpioManager, communicationQueue, *it));
            } else if (moduleName == TelegramBotModule::k_moduleName) {
                m_modules.emplace_back(new TelegramBotModule(communicationQueue, *it));
            }
        }
    }
}

void App::signalHandler(int /*signal*/)
{
    App::getInstance().exit();
}
