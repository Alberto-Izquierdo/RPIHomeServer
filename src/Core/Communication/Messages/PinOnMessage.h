#ifndef PINONMESSAGE_H
#define PINONMESSAGE_H

#include <Core/Communication/Message.h>
#include <string>

namespace core
{
class PinOnMessage : public Message
{
public:
    PinOnMessage(const std::string &pinAlias) noexcept;
    ~PinOnMessage() noexcept final;

    const std::string &getPinAlias() const noexcept { return m_pinAlias; }

private:
    const std::string m_pinAlias;
};
}  // namespace core

#endif
