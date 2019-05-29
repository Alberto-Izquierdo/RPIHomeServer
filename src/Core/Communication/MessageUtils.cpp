#include "MessageUtils.h"

using namespace core::MessageUtils;

const std::unordered_map<MessageType, std::string> typeToString = {{MessageType::EXIT, "exit"},
                                                                   {MessageType::LIGHT_ON, "lightOn"},
                                                                   {MessageType::LIGHT_OFF, "lightOff"},
                                                                   {MessageType::PIN_ON, "pinOn"},
                                                                   {MessageType::PIN_OFF, "pinOff"}};

std::string getMessageTypeName(MessageType type) noexcept
{
    auto it = typeToString.find(type);
    if (it != typeToString.end()) {
        return it->second;
    }
    return "None";
}

MessageType getMessageType(const std::string &typeName) noexcept
{
    static std::unordered_map<std::string, MessageType> stringToType;
    if (stringToType.empty()) {
        for (const auto &pair : typeToString) {
            stringToType.insert({pair.second, pair.first});
        }
    }
    auto it = stringToType.find(typeName);
    if (it != stringToType.end()) {
        return it->second;
    }
    return MessageType::NONE;
}
