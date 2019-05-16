#include "App.h"
#include <Core/Modules/CommunicationModule.h>
#include <Core/Modules/GPIOModule.h>
#include <Core/Modules/TelegramBotModule.h>
#include <Core/Communication/Message.h>
#include <Gpio/GpioManager.h>
#include <thread>
#include <iostream>
#include <signal.h>

App &App::getInstance()
{
    static App app;
    return app;
}

App::App() noexcept
    : m_gpioManager(std::make_shared<GPIO::GpioManager>())
{
    signal(SIGINT, App::signalHandler);
}

App::~App() noexcept
{
}

bool App::init() noexcept
{
    // Build modules
    auto communicationModule(new core::CommunicationModule());
    auto &communicationQueue = communicationModule->getInputQueue();

    m_modules.emplace_back(new core::GPIOModule(m_gpioManager, communicationQueue));
    m_modules.emplace_back(new core::TelegramBotModule(communicationQueue));

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
        threads.emplace_back(&core::BaseModule::start, module.get());
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
        if (module->getType() == core::BaseModule::Type::COMMUNICATION) {
            auto exitMessage = std::make_shared<core::Message>(core::MessageType::EXIT);
            module->getInputQueue()->push(exitMessage);
            return;
        }
    }
}

void App::signalHandler(int /*signal*/)
{
    App::getInstance().exit();
}
