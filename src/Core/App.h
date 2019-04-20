#ifndef APP_H
#define APP_H

#include <vector>
#include <memory>

namespace GPIO
{
class GpioManager;
}  // namespace GPIO

namespace core
{
class BaseModule;
}  // namespace core

class App
{
public:
    static App &getInstance();
    void init() noexcept;

    void start() noexcept;

    void exit() noexcept;

    static void signalHandler(int signal);

    // Delete copy/assign
    App(const App &) = delete;
    App &operator=(const App &) const = delete;

private:
    App() noexcept;
    ~App() noexcept;
    std::vector<std::unique_ptr<core::BaseModule>> m_modules;
    std::shared_ptr<GPIO::GpioManager> m_gpioManager;
};

#endif  // APP_H
