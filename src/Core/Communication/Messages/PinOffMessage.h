#ifndef PINOFFMESSAGE_H
#define PINOFFMESSAGE_H

#include <Core/Communication/Message.h>
#include <string>

namespace core
{
class PinOffMessage : public Message
{
public:
    PinOffMessage(const std::string &pinAlias) noexcept;
    ~PinOffMessage() noexcept final;

    const std::string &getPinAlias() const noexcept { return m_pinAlias; }

private:
    const std::string m_pinAlias;
};
}  // namespace core

#endif
