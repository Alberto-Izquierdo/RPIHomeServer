#include "MessageFactory.h"
#include <Core/Communication/MessageUtils.h>
#include <Core/Communication/Messages/PinOnMessage.h>
#include <Core/Communication/Messages/PinOffMessage.h>
#include <Core/Communication/Messages/PinOnAndOffMessage.h>
#include <iostream>

using namespace core;

const std::unordered_map<MessageType, std::shared_ptr<Message> (*)(const nlohmann::json &json), std::hash<int>>
    messageConstructors = {{MessageType::PIN_ON, &MessageFactory::makePinOnMessage},
                           {MessageType::PIN_OFF, &MessageFactory::makePinOffMessage},
                           {MessageType::PIN_ON_AND_OFF, &MessageFactory::makePinOnAndOffMessage}};

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
        auto alias = json.find("alias");
        if (alias != json.end() && alias.value().is_string()) {
            return std::make_shared<PinOnMessage>(alias.value());
        }
    }
    return nullptr;
}

std::shared_ptr<Message> MessageFactory::makePinOffMessage(const nlohmann::json &json) noexcept
{
    if (json.is_object()) {
        auto alias = json.find("alias");
        if (alias != json.end() && alias.value().is_string()) {
            return std::make_shared<PinOffMessage>(alias.value());
        }
    }
    return nullptr;
}

std::shared_ptr<Message> MessageFactory::makePinOnAndOffMessage(const nlohmann::json &json) noexcept
{
    if (json.is_object()) {
        auto alias = json.find("alias");
        auto durationJson = json.find("duration");
        if (alias != json.end() && alias.value().is_string() && durationJson != json.end() &&
            durationJson.value().is_string()) {
            auto duration = MessageUtils::getDurationFromString(durationJson.value());
            return std::make_shared<PinOnAndOffMessage>(alias.value(), duration);
        }
    }
    return nullptr;
}
