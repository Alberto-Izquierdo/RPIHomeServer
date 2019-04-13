#include "GpioController.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace GPIO;

GpioController::GpioController(const std::string &pin)
    : m_pin(pin)
    , m_value(false)
{
    std::string export_str = "/sys/class/gpio/export";
    std::ofstream exportgpio(export_str.c_str()); // Open "export" file. Convert C++ std::string to C std::string. Required for all Linux pathnames
    /*if (exportgpio < 0){
        std::cout << "OPERATION FAILED: Unable to export GPIO" << m_pin << std::endl;
        return;
    }*/

    exportgpio << m_pin; //write GPIO number to export
    exportgpio.close(); //close export file
}

GpioController::~GpioController()
{
    std::string unexport_str = "/sys/class/gpio/unexport";
    std::ofstream unexportgpio(unexport_str.c_str()); //Open unexport file
    /*if (unexportgpio < 0){
        std::cout << "OPERATION FAILED: Unable to unexport GPIO" << m_pin << std::endl;
        return;
    }*/

    unexportgpio << m_pin; //write GPIO number to unexport
    unexportgpio.close(); //close unexport file
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
    std::string setval_str = "/sys/class/gpio/gpio" + value + "/value";
    std::ofstream setvalgpio(setval_str.c_str()); // open value file for gpio
    /*if (setvalgpio < 0){
        std::cout << "OPERATION FAILED: Unable to set the value of GPIO" << m_pin << std::endl;
        return false;
    }*/
    setvalgpio << value ;//write value to value file
    setvalgpio.close();// close value file
    return true;
}
