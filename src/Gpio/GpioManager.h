#ifndef GPIOMANAGER_H
#define GPIOMANAGER_H

#include <unordered_map>
#include "GpioController.h"

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
    std::unordered_map<int, GpioController> m_controllers;
};
}  // namespace GPIO

#endif
