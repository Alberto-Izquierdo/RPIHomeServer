#ifndef GPIOCONTROLLER_H
#define GPIOCONTROLLER_H

#include <string>

namespace GPIO {
// For now all GpioControllers are for out direction
class GpioController {
  friend class GpioManager;

  explicit GpioController(const std::string &pin);
  GpioController() = delete;

  bool on() noexcept;
  bool off() noexcept;

  bool setValue(const std::string &value) noexcept;

  std::string m_pin;
  bool m_value;
public:
  ~GpioController();
};
} // namespace GPIO

#endif
