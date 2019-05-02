#include "GpioManager.h"
#include <iostream>

using namespace GPIO;

void GpioManager::setupController(int pin) noexcept
{
    auto it = m_controllers.find(pin);
    if (it == m_controllers.end()) {
        auto controller = std::unique_ptr<GpioController>(new GpioController(std::to_string(pin)));
        m_controllers.insert(std::make_pair(pin, std::move(controller)));
    } else {
        std::cout << "OPERATION FAILED: Unable to setup pin " << pin << ", pin already in use" << std::endl;
    }
}

void GpioManager::releaseController(int pin) noexcept
{
    auto it = m_controllers.find(pin);
    if (it != m_controllers.end()) {
        m_controllers.erase(it);
    } else {
        std::cout << "OPERATION FAILED: Unable to release pin " << pin << ", pin not set" << std::endl;
    }
}

void GpioManager::setPinOn(int pin) noexcept
{
    auto it = m_controllers.find(pin);
    if (it != m_controllers.end()) {
        it->second->on();
    } else {
        std::cout << "OPERATION FAILED: Unable to use pin " << pin << ", pin not set" << std::endl;
    }
}

void GpioManager::setPinOff(int pin) noexcept
{
    auto it = m_controllers.find(pin);
    if (it != m_controllers.end()) {
        it->second->off();
    } else {
        std::cout << "OPERATION FAILED: Unable to use pin " << pin << ", pin not set" << std::endl;
    }
}
