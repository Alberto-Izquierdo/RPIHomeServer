#include "MessageFactory.h"
#include <Core/Communication/MessageUtils.h>
#include <Core/Communication/Messages/PinOnMessage.h>
#include <Core/Communication/Messages/PinOffMessage.h>
#include <iostream>

using namespace core;

const std::unordered_map<MessageType, std::shared_ptr<Message> (*)(const nlohmann::json &json), std::hash<int>>
    messageConstructors = {{MessageType::PIN_ON, &MessageFactory::makePinOnMessage},
                           {MessageType::PIN_OFF, &MessageFactory::makePinOffMessage}};

std::shared_ptr<Message> MessageFactory::makeMessage(const nlohmann::json &json) noexcept
{
    if (json.is_object()) {
        MessageType messageType = MessageUtils::getMessageType(json.begin().key());
        auto res = messageConstructors.find(messageType);
        if (res != messageConstructors.end()) {
            return (*res->second)(json.begin().value());
        }
    }
    return nullptr;
}

std::shared_ptr<Message> MessageFactory::makePinOnMessage(const nlohmann::json &json) noexcept
{
    if (json.is_object()) {
        auto it = json.find("alias");
        if (it != json.end()) {
            return std::make_shared<PinOnMessage>(json["alias"]);
        }
    }
    return nullptr;
}

std::shared_ptr<Message> MessageFactory::makePinOffMessage(const nlohmann::json &json) noexcept
{
    if (json.is_object()) {
        auto it = json.find("alias");
        if (it != json.end()) {
            return std::make_shared<PinOffMessage>(json["alias"]);
        }
    }
    return nullptr;
}
