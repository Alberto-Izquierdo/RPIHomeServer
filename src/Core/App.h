#ifndef APP_H
#define APP_H

#include <vector>
#include <memory>
#include <Core/MultithreadQueue.h>

namespace GPIO
{
class GpioManager;
}  // namespace GPIO

namespace core
{
class BaseModule;
class Message;
}  // namespace core

class App
{
public:
    static App &getInstance() noexcept;
    bool init() noexcept;

    void start() noexcept;

    void exit() noexcept;

    static void signalHandler(int signal);

private:
    App() noexcept;
    ~App() noexcept;
    bool loadModules(
        const std::string &configFilePath,
        std::shared_ptr<core::MultithreadQueue<std::shared_ptr<core::Message>>> &communicationQueue) noexcept;
    std::vector<std::unique_ptr<core::BaseModule>> m_modules;
    std::shared_ptr<GPIO::GpioManager> m_gpioManager;
    const std::vector<std::string> m_moduleNames;
};

#endif  // APP_H
