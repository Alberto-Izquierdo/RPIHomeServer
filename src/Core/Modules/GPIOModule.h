#ifndef GPIO_MODULE_H
#define GPIO_MODULE_H

#include <Core/BaseModule.h>
#include <nlohmann/json.hpp>

namespace GPIO
{
class GpioManager;
}  // namespace GPIO

namespace core
{
class GPIOModule : public BaseModule
{
public:
    GPIOModule(std::shared_ptr<GPIO::GpioManager> &gpioManager,
               std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> &outputQueue,
               const nlohmann::json &config) noexcept;
    ~GPIOModule() noexcept final;

    bool init() noexcept final;

    void specificStart() noexcept final;
    void specificExit() noexcept final;
    const std::string &getModuleName() const noexcept final { return k_moduleName; }

    void handlePinChanged(const std::shared_ptr<Message> message) noexcept;
    void getAvailableMessages(const std::shared_ptr<Message> message) noexcept;
    void turnPinOn(std::string pinAlias) noexcept;
    void turnPinOff(std::string pinAlias) noexcept;
    /*
    void turnLightOn(const std::shared_ptr<Message> message);
    void turnLightOff(const std::shared_ptr<Message> message);
    */

    GPIOModule() = delete;

    static const std::string k_moduleName;

private:
    std::shared_ptr<GPIO::GpioManager> m_gpioManager;
    std::unordered_map<std::string, int> m_pinsAssigned;
};
}  // namespace core

#endif
