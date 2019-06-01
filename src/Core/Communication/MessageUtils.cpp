#include "MessageUtils.h"

using namespace core;

static const std::unordered_map<MessageType, std::string, std::hash<int>> typeToString = {
    {MessageType::EXIT, "exit"},
    {MessageType::PIN_ON, "pinOn"},
    {MessageType::PIN_OFF, "pinOff"}};

std::string MessageUtils::getMessageTypeName(MessageType type) noexcept
{
    auto it = typeToString.find(type);
    if (it != typeToString.end()) {
        return it->second;
    }
    return "None";
}

MessageType MessageUtils::getMessageType(const std::string &typeName) noexcept
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

std::chrono::time_point<std::chrono::system_clock> MessageUtils::getTimeFromString(const std::string &time) noexcept
{
    auto now = std::chrono::system_clock::now();
    try {
        time_t tmp = std::chrono::system_clock::to_time_t(now);
        tm actualTime = *localtime(&tmp);
        tm timeToWakeUpTm = actualTime;
        strptime(time.c_str(), "%H:%M:%S", &timeToWakeUpTm);
        return std::chrono::system_clock::from_time_t(mktime(&timeToWakeUpTm));
    } catch (...) {
        return now - std::chrono::hours(1);
    }
}
