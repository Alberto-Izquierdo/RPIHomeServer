#include "GpioController.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace GPIO;

GpioController::GpioController(const std::string &pin)
    : m_pin(pin)
{
    std::string exportStr = "/sys/class/gpio/export";
    std::ofstream exportGpio(exportStr.c_str());
    if (exportGpio.bad()) {
        std::cout << "OPERATION FAILED: Unable to export GPIO" << m_pin << std::endl;
        return;
    }
    exportGpio << m_pin;
    exportGpio.close();

    std::string direction = "/sys/class/gpio/gpio" + m_pin + "/direction";
    std::ofstream directionGpio(direction.c_str());
    if (directionGpio.bad()) {
        std::cout << "OPERATION FAILED: Unable to set direction on GPIO" << m_pin << std::endl;
        return;
    }
    directionGpio << "out";
    directionGpio.close();
}

GpioController::~GpioController()
{
    off();
    std::string unexportStr = "/sys/class/gpio/unexport";
    std::ofstream unexportGpio(unexportStr.c_str());
    if (unexportGpio.bad()) {
        std::cout << "OPERATION FAILED: Unable to unexport GPIO" << m_pin << std::endl;
        return;
    }
    unexportGpio << m_pin;
    unexportGpio.close();
}

bool GpioController::on() noexcept
{
    return setValue("1");
}

bool GpioController::off() noexcept
{
    return setValue("0");
}

bool GpioController::setValue(const std::string &value) noexcept
{
    std::string setValStr = "/sys/class/gpio/gpio" + m_pin + "/value";
    std::ofstream setValGpio(setValStr.c_str());
    if (setValGpio.bad()) {
        std::cout << "OPERATION FAILED: Unable to set the value of GPIO" << m_pin << std::endl;
        return false;
    }
    setValGpio << value;
    setValGpio.close();
    return true;
}
