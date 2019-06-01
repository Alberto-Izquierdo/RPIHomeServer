#ifndef MESSAGEUTILS_H
#define MESSAGEUTILS_H

#include <Core/Communication/MessageTypes.h>
#include <unordered_map>
#include <string>
#include <chrono>

namespace core
{
namespace MessageUtils
{
std::string getMessageTypeName(MessageType type) noexcept;
MessageType getMessageType(const std::string &typeName) noexcept;
std::chrono::time_point<std::chrono::system_clock> getTimeFromString(const std::string &time) noexcept;
}  // namespace MessageUtils
}  // namespace core
#endif
