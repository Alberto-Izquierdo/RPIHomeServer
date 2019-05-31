#ifndef MESSAGEUTILS_H
#define MESSAGEUTILS_H

#include <Core/Communication/MessageTypes.h>
#include <unordered_map>
#include <string>

namespace core
{
namespace MessageUtils
{
std::string getMessageTypeName(MessageType type) noexcept;
MessageType getMessageType(const std::string &typeName) noexcept;
}  // namespace MessageUtils
}  // namespace core
#endif
