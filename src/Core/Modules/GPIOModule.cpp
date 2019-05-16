#include "GPIOModule.h"
#include <Gpio/GpioManager.h>
#include <iostream>

using namespace core;

const std::string GPIOModule::m_moduleName = "Light";

GPIOModule::GPIOModule(std::shared_ptr<GPIO::GpioManager> &gpioManager,
                       std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> &outputQueue) noexcept
    : BaseModule(BaseModule::Type::LIGHT, outputQueue)
    , m_gpioManager(gpioManager)
{
    addMessageHandler(core::MessageType::LIGHT_ON,
                      reinterpret_cast<BaseModule::messageHanlderFunction>(&GPIOModule::turnLightOn));
    addMessageHandler(core::MessageType::LIGHT_OFF,
                      reinterpret_cast<BaseModule::messageHanlderFunction>(&GPIOModule::turnLightOff));
}

bool GPIOModule::init() noexcept
{
    m_pinAssignedToLight = 18;
    m_gpioManager->setupController(m_pinAssignedToLight);
    return true;
}

GPIOModule::~GPIOModule() noexcept
{
}

void GPIOModule::specificStart() noexcept
{
}

void GPIOModule::specificExit() noexcept
{
}

void GPIOModule::turnLightOn(const std::shared_ptr<Message> /*message*/)
{
    std::cout << "Light on" << std::endl;
    m_gpioManager->setPinOn(m_pinAssignedToLight);
}

void GPIOModule::turnLightOff(const std::shared_ptr<Message> /*message*/)
{
    std::cout << "Light off" << std::endl;
    m_gpioManager->setPinOff(m_pinAssignedToLight);
}

const std::string &GPIOModule::getModuleName() const noexcept
{
    return m_moduleName;
}
