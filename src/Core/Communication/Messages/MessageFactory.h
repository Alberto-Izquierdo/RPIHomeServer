#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H

#include <Core/Communication/MessageTypes.h>
#include <nlohmann/json.hpp>
#include <memory>

namespace core
{
class Message;
}  // namespace core

namespace core
{
namespace MessageFactory
{
std::shared_ptr<Message> makeMessage(const nlohmann::json &json) noexcept;
static std::shared_ptr<Message> makePinOnMessage(const nlohmann::json &json) noexcept;
static std::shared_ptr<Message> makePinOffMessage(const nlohmann::json &json) noexcept;
}  // namespace MessageFactory
}  // namespace core

#endif
