#ifndef MESSAGEUTILS_H
#define MESSAGEUTILS_H

#include <Core/Communication/MessageTypes.h>
#include <unordered_map>
#include <string>

namespace core
{
namespace utils
{
static const std::unordered_map<MessageType, std::string, std::hash<int>> typeToString;
std::string getMessageTypeName(MessageType type) noexcept;
MessageType getMessageType(const std::string &typeName) noexcept;
}  // namespace utils
}  // namespace core
#endif
