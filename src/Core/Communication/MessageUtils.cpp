#include "MessageUtils.h"

using namespace core;

static const std::unordered_map<MessageType, std::string, std::hash<int>> typeToString = {
    {MessageType::EXIT, "exit"},
    {MessageType::PIN_ON, "pinOn"},
    {MessageType::PIN_OFF, "pinOff"},
    {MessageType::PIN_ON_AND_OFF, "pinOnAndOff"}};

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
        tm resultTM = *localtime(&tmp);
        auto lastCharProcessed = strptime(time.c_str(), "%H:%M:%S", &resultTM);
        if (lastCharProcessed != nullptr) {
            auto result = std::chrono::system_clock::from_time_t(mktime(&resultTM));
            if (result < now) {
                result += std::chrono::hours(24);
            }
            return result;
        } else {
            return now - std::chrono::hours(1);
        }
    } catch (...) {
        return now - std::chrono::hours(1);
    }
}

std::chrono::duration<int> MessageUtils::getDurationFromString(const std::string &time) noexcept
{
    try {
        tm duration_t{0};
        strptime(time.c_str(), "%H:%M:%S", &duration_t);
        std::chrono::duration<int> duration = std::chrono::seconds(duration_t.tm_sec);
        duration += std::chrono::minutes(duration_t.tm_min);
        duration += std::chrono::hours(duration_t.tm_hour);
        return duration;
    } catch (...) {
        return std::chrono::seconds(0);
    }
}
