#ifndef GPIOCONTROLLER_H
#define GPIOCONTROLLER_H

#include <string>

namespace GPIO
{
// For now all GpioControllers are for out direction
class GpioController
{
public:
    explicit GpioController(const std::string &pin);
    ~GpioController();

    bool on() noexcept;
    bool off() noexcept;

private:
    bool setValue(const std::string &value) noexcept;

    std::string m_pin;
};
}  // namespace GPIO

#endif
