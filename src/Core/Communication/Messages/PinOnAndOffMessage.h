#ifndef PIN_ON_AND_OFF_MESSAGE_H
#define PIN_ON_AND_OFF_MESSAGE_H

#include <Core/Communication/Message.h>
#include <string>
#include <chrono>

namespace core
{
class PinOnAndOffMessage : public Message
{
public:
    PinOnAndOffMessage(const std::string &pinAlias, std::chrono::duration<int> timeToSwitchOff) noexcept;
    ~PinOnAndOffMessage() noexcept final;

    const std::string &getPinAlias() const noexcept { return m_pinAlias; }
    std::chrono::duration<int> getTimeToSwitchOff() const noexcept { return m_timeToSwitchOff; }

private:
    const std::string m_pinAlias;
    const std::chrono::duration<int> m_timeToSwitchOff;
};
}  // namespace core

#endif
