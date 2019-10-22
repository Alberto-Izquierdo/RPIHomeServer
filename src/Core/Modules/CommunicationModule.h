#ifndef COMMUNICATIONMODULE_H
#define COMMUNICATIONMODULE_H

#include <Core/BaseModule.h>

namespace core
{
class MessageDispatcher;
class CommunicationModule : public BaseModule
{
public:
    explicit CommunicationModule() noexcept;
    ~CommunicationModule() noexcept final;

    bool init() noexcept final;
    void specificStart() noexcept final;
    void specificExit() noexcept final;
    std::string_view getModuleName() const noexcept final { return k_moduleName; }
    void setup(const std::vector<std::unique_ptr<BaseModule>> &modules) noexcept;
    void handleMessage(const std::shared_ptr<Message> &message) noexcept final;

    static constexpr const char *k_moduleName = "Communication";

private:
    std::unique_ptr<MessageDispatcher> m_messageDispatcher;
};
}  // namespace core

#endif
