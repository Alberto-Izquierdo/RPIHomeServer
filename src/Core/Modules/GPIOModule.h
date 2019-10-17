#ifndef GPIO_MODULE_H
#define GPIO_MODULE_H

#include <Core/BaseModule.h>
#include <nlohmann/json.hpp>
#include <set>

namespace GPIO
{
class GpioManager;
}  // namespace GPIO

namespace core
{
struct PinToTurnOff {
    PinToTurnOff(const std::string &alias, const std::chrono::time_point<std::chrono::system_clock> &timeToSwitchOff)
        : alias(alias)
        , timeToSwitchOff(timeToSwitchOff)
    {
    }
    std::string alias;
    std::chrono::time_point<std::chrono::system_clock> timeToSwitchOff;
};

struct PinToTurnOffComparator {
    bool operator()(const PinToTurnOff &lhs, const PinToTurnOff &rhs) const
    {
        return lhs.timeToSwitchOff < rhs.timeToSwitchOff;
    }
};

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
    void update() noexcept final;
    const std::string &getModuleName() const noexcept final { return k_moduleName; }

    void handlePinChanged(const std::shared_ptr<Message> message) noexcept;
    void handlePinOnAndOff(const std::shared_ptr<Message> message) noexcept;
    void getAvailableMessages(const std::shared_ptr<Message> message) noexcept;
    void turnPinOn(std::string pinAlias) noexcept;
    void turnPinOff(std::string pinAlias) noexcept;
    void turnPinOnAndOff(std::string pinAlias, std::chrono::duration<int> duration) noexcept;
    void removePinToSwitchOffIfExists(const std::string &alias) noexcept;
    /*
    void turnLightOn(const std::shared_ptr<Message> message);
    void turnLightOff(const std::shared_ptr<Message> message);
    */

    GPIOModule() = delete;

    static const std::string k_moduleName;

private:
    std::shared_ptr<GPIO::GpioManager> m_gpioManager;
    std::unordered_map<std::string, int> m_pinsAssigned;
    std::set<PinToTurnOff, PinToTurnOffComparator> m_pinsToTurnOff;
};
}  // namespace core

#endif
