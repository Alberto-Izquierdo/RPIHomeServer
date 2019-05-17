#include "GPIOModule.h"
#include <Gpio/GpioManager.h>
#include <iostream>

using namespace core;

const std::string GPIOModule::k_moduleName = "GPIO";

GPIOModule::GPIOModule(std::shared_ptr<GPIO::GpioManager> &gpioManager,
                       std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> &outputQueue,
                       const nlohmann::json &config) noexcept
    : BaseModule(BaseModule::Type::GPIO, outputQueue)
    , m_gpioManager(gpioManager)
{
    addMessageHandler(core::MessageType::LIGHT_ON,
                      reinterpret_cast<BaseModule::messageHanlderFunction>(&GPIOModule::turnLightOn));
    addMessageHandler(core::MessageType::LIGHT_OFF,
                      reinterpret_cast<BaseModule::messageHanlderFunction>(&GPIOModule::turnLightOff));
    m_pinAssignedToLight = config.value("lightPin", 18);
}

bool GPIOModule::init() noexcept
{
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
