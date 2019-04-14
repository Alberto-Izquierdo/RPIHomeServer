#ifndef GPIOMANAGER_H
#define GPIOMANAGER_H

#include "GpioController.h"
#include <unordered_map>
#include <memory>

namespace GPIO
{
class GpioManager
{
public:
    explicit GpioManager() = default;

    void setupController(int pin) noexcept;
    void releaseController(int pin) noexcept;

    void setPinOn(int pin) noexcept;
    void setPinOff(int pin) noexcept;
    // TODO
    // bool getValueFromPin(int pin) const;

private:
    std::unordered_map<int, std::unique_ptr<GpioController>> m_controllers;
};
}  // namespace GPIO

#endif
