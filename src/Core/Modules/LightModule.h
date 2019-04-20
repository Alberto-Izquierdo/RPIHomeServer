#ifndef LIGHTMODULE_H
#define LIGHTMODULE_H

#include <Core/BaseModule.h>

namespace GPIO
{
class GpioManager;
}  // namespace GPIO

namespace core
{
class LightModule : public BaseModule
{
public:
    LightModule(std::shared_ptr<GPIO::GpioManager> &gpioManager,
                std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> &outputQueue) noexcept;
    ~LightModule() noexcept final;

    void specificStart() noexcept final;
    void specificExit() noexcept final;
    const std::string &getModuleName() const noexcept final;

    void turnOn(const std::shared_ptr<Message> message);
    void turnOff(const std::shared_ptr<Message> message);

    LightModule() = delete;

private:
    static const std::string m_moduleName;
    std::shared_ptr<GPIO::GpioManager> m_gpioManager;
    int m_pinAssigned;
};
}  // namespace core

#endif
