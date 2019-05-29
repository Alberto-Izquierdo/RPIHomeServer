#include "GPIOModule.h"
#include <Gpio/GpioManager.h>
#include <iostream>
#include <algorithm>
#include <Core/Communication/Messages/PinOnMessage.h>
#include <Core/Communication/Messages/PinOffMessage.h>
#include <Core/Communication/Messages/ReturnAvailablePinsMessage.h>
#include <Core/Communication/Messages/GetAvailablePinsMessage.h>

using namespace core;

const std::string GPIOModule::k_moduleName = "GPIO";

GPIOModule::GPIOModule(std::shared_ptr<GPIO::GpioManager> &gpioManager,
                       std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> &outputQueue,
                       const nlohmann::json &config) noexcept
    : BaseModule(BaseModule::Type::GPIO, outputQueue)
    , m_gpioManager(gpioManager)
{
    addMessageHandler(core::MessageType::PIN_ON,
                      reinterpret_cast<BaseModule::messageHanlderFunction>(&GPIOModule::handlePinChanged));
    addMessageHandler(core::MessageType::PIN_OFF,
                      reinterpret_cast<BaseModule::messageHanlderFunction>(&GPIOModule::handlePinChanged));
    addMessageHandler(core::MessageType::GET_AVAILABLE_PIN_ALIASES,
                      reinterpret_cast<BaseModule::messageHanlderFunction>(&GPIOModule::getAvailableMessages));
    auto pins = config.find("pins");
    if (pins != config.end()) {
        if (pins->is_array()) {
            try {
                const auto pinsV = pins->get<std::vector<std::pair<std::string, int>>>();
                for (auto pin : pinsV) {
                    auto pinAlias = pin.first;
                    auto pinNumber = pin.second;
                    m_pinsAssigned[pinAlias] = pinNumber;
                }
            } catch (...) {
                std::cout << "Pin array not well defined" << std::endl;
            }
        }
    }
}

bool GPIOModule::init() noexcept
{
    if (m_pinsAssigned.empty()) {
        return false;
    }
    for (const auto &pair : m_pinsAssigned) {
        m_gpioManager->setupController(pair.second);
    }
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

void GPIOModule::handlePinChanged(const std::shared_ptr<Message> message) noexcept
{
    if (message->getType() == MessageType::PIN_ON) {
        auto castedMessage = std::static_pointer_cast<PinOnMessage>(message);
        turnPinOn(castedMessage->getPinAlias());
    } else if (message->getType() == MessageType::PIN_OFF) {
        auto castedMessage = std::static_pointer_cast<PinOffMessage>(message);
        turnPinOff(castedMessage->getPinAlias());
    }
}

void GPIOModule::getAvailableMessages(const std::shared_ptr<Message> message) noexcept
{
    auto castedMessage = std::static_pointer_cast<GetAvailablePinsMessage>(message);
    std::vector<std::string> pinsAssigned;
    pinsAssigned.reserve(m_pinsAssigned.size());
    std::transform(m_pinsAssigned.begin(),
                   m_pinsAssigned.end(),
                   std::back_inserter(pinsAssigned),
                   [&](const std::pair<std::string, int> &pair) -> const std::string & { return pair.first; });
    auto outputMessage = std::make_shared<ReturnAvailablePinsMessage>(pinsAssigned, castedMessage->getChatId());
    getOutputQueue()->push(outputMessage);
}

void GPIOModule::turnPinOn(std::string pinAlias) noexcept
{
    auto it = m_pinsAssigned.find(pinAlias);
    if (it != m_pinsAssigned.end()) {
        std::cout << it->first << " on" << std::endl;
        m_gpioManager->setPinOn(it->second);
    } else {
        // TODO: return error message
        std::cout << "Pin not set" << std::endl;
    }
}

void GPIOModule::turnPinOff(std::string pinAlias) noexcept
{
    auto it = m_pinsAssigned.find(pinAlias);
    if (it != m_pinsAssigned.end()) {
        std::cout << it->first << " off" << std::endl;
        m_gpioManager->setPinOff(it->second);
    } else {
        // TODO: return error message
        std::cout << "Pin not set" << std::endl;
    }
}

// void GPIOModule::turnLightOn(const std::shared_ptr<Message> /*message*/)
//{
// std::cout << "Light on" << std::endl;
// m_gpioManager->setPinOn(m_pinAssignedToLight);
//}

// void GPIOModule::turnLightOff(const std::shared_ptr<Message> /*message*/)
//{
// std::cout << "Light off" << std::endl;
// m_gpioManager->setPinOff(m_pinAssignedToLight);
//}
