#include "App.h"
#include "BaseModule.h"
#include "Modules/CommunicationModule.h"
#include <thread>

App::App() noexcept
{
}

App::~App() noexcept
{
}

void App::init() noexcept
{
    // Build modules
    auto communicationModule = std::make_unique<core::CommunicationModule>();
    auto communicationQueue = communicationModule->getInputQueue();

    // Setup message dispatcher
    std::vector<core::BaseModule *> modules;
    communicationModule->setup(modules);

    m_modules.push_back(std::move(communicationModule));
}

void App::start() noexcept
{
    std::vector<std::thread> threads;
    threads.reserve(m_modules.size());
    // Start modules
    for (auto &module : m_modules) {
        threads.emplace_back(&core::BaseModule::start, module.get());
    }
    for (auto &thread : threads) {
        thread.join();
    }
}
