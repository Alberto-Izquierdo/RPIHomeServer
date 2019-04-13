#include "GpioController.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace GPIO;

GpioController::GpioController(const std::string &pin)
    : m_pin(pin)
    , m_value(false)
{
    std::string exportStr = "/sys/class/gpio/export";
    std::ofstream exportGpio(exportStr.c_str()); // Open "export" file. Convert C++ std::string to C std::string. Required for all Linux pathnames
    /*if (exportgpio < 0){
        std::cout << "OPERATION FAILED: Unable to export GPIO" << m_pin << std::endl;
        return;
    }*/
    exportGpio << m_pin; //write GPIO number to export
    exportGpio.close(); //close export file

    std::string direction = "/sys/class/gpio/gpio" + m_pin + "/direction";
    std::ofstream directionGpio(direction.c_str()); // open value file for gpio
    directionGpio << "out" ;//write value to value file
    directionGpio.close(); //close export file
}

GpioController::~GpioController()
{
    std::string unexportStr = "/sys/class/gpio/unexport";
    std::ofstream unexportGpio(unexportStr.c_str()); //Open unexport file
    /*if (unexportgpio < 0){
        std::cout << "OPERATION FAILED: Unable to unexport GPIO" << m_pin << std::endl;
        return;
    }*/

    unexportGpio << m_pin; //write GPIO number to unexport
    unexportGpio.close(); //close unexport file
}

bool GpioController::on() noexcept
{
    m_value = true;
    return setValue("1");
}

bool GpioController::off() noexcept
{
    m_value = true;
    return setValue("0");
}

bool GpioController::setValue(const std::string &value) noexcept
{
    std::string setValStr = "/sys/class/gpio/gpio" + m_pin + "/value";
    std::ofstream setValGpio(setValStr.c_str()); // open value file for gpio
    /*if (setvalgpio < 0){
        std::cout << "OPERATION FAILED: Unable to set the value of GPIO" << m_pin << std::endl;
        return false;
    }*/
    setValGpio << value ;//write value to value file
    setValGpio.close();// close value file
    return true;
}
