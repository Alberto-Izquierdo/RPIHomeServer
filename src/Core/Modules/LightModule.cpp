#include "LightModule.h"
#include <Gpio/GpioManager.h>
#include <iostream>

using namespace core;

const std::string LightModule::m_moduleName = "Light";

LightModule::LightModule(std::shared_ptr<GPIO::GpioManager> &gpioManager,
                         std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> &outputQueue) noexcept
    : BaseModule(BaseModule::Type::LIGHT, outputQueue)
    , m_gpioManager(gpioManager)
    , m_pinAssigned(17)
{
    m_gpioManager->setupController(m_pinAssigned);
    addMessageHandler(core::MessageType::LIGHT_ON,
                      reinterpret_cast<BaseModule::messageHanlderFunction>(&LightModule::turnOn));
    addMessageHandler(core::MessageType::LIGHT_OFF,
                      reinterpret_cast<BaseModule::messageHanlderFunction>(&LightModule::turnOff));
}

LightModule::~LightModule() noexcept
{
}

void LightModule::specificStart() noexcept
{
}

void LightModule::specificExit() noexcept
{
}

void LightModule::turnOn(const std::shared_ptr<Message> /*message*/)
{
    std::cout << "Light on" << std::endl;
    m_gpioManager->setPinOn(m_pinAssigned);
}

void LightModule::turnOff(const std::shared_ptr<Message> /*message*/)
{
    std::cout << "Light off" << std::endl;
    m_gpioManager->setPinOff(m_pinAssigned);
}

const std::string &LightModule::getModuleName() const noexcept
{
    return m_moduleName;
}
