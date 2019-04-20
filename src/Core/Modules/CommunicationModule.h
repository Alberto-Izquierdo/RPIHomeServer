#ifndef COMMUNICATIONMODULE_H
#define COMMUNICATIONMODULE_H

#include "../BaseModule.h"

namespace core
{
class MessageDispatcher;
class CommunicationModule : public BaseModule
{
public:
    explicit CommunicationModule() noexcept;
    ~CommunicationModule() noexcept final;

    void specificStart() noexcept final;
    void specificExit() noexcept final;
    void setup(const std::vector<BaseModule *> &modules) noexcept;
    void handleMessage(const std::shared_ptr<Message> message) noexcept final;

private:
    std::unique_ptr<MessageDispatcher> m_messageDispatcher;
};
}  // namespace core

#endif
