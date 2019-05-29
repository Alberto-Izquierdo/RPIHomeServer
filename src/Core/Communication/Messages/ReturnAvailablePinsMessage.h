#ifndef RETURN_AVAILABLE_PIN_SMESSAGE_H
#define RETURN_AVAILABLE_PIN_SMESSAGE_H

#include <Core/Communication/Message.h>
#include <vector>
#include <string>

namespace core
{
class ReturnAvailablePinsMessage : public Message
{
public:
    ReturnAvailablePinsMessage(const std::vector<std::string> &pinsAvailable, uint64_t chatId) noexcept;
    ~ReturnAvailablePinsMessage() noexcept final;

    const std::vector<std::string> &getPinsAvailable() const noexcept { return m_pinsAvailable; }
    uint64_t getChatId() const noexcept { return m_chatId; }

private:
    const std::vector<std::string> m_pinsAvailable;
    uint64_t m_chatId;
};
}  // namespace core

#endif
