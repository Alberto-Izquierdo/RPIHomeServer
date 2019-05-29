#ifndef GET_AVAILABLE_PINS_MESSAGE_H
#define GET_AVAILABLE_PINS_MESSAGE_H

#include <Core/Communication/Message.h>
#include <cstdint>

namespace core
{
class GetAvailablePinsMessage : public Message
{
public:
    GetAvailablePinsMessage(uint64_t chatId) noexcept;
    ~GetAvailablePinsMessage() noexcept final;

    uint64_t getChatId() const noexcept { return m_chatId; }

private:
    uint64_t m_chatId;
};
}  // namespace core

#endif
