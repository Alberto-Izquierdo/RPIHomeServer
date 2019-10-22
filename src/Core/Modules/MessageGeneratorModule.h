#ifndef MESSAGEGENERATORMODULE_H
#define MESSAGEGENERATORMODULE_H

#include <Core/BaseModule.h>
#include <nlohmann/json.hpp>
#include <set>
#include <chrono>

namespace core
{
struct MessagesToLaunch {
    explicit MessagesToLaunch(std::shared_ptr<Message> &message,
                              std::chrono::time_point<std::chrono::system_clock> &&nextTimeToLaunch,
                              std::chrono::duration<int> frequency)
        : message(message)
        , nextTimeToLaunch(nextTimeToLaunch)
        , frequency(frequency)
    {
    }
    std::shared_ptr<Message> message;
    std::chrono::time_point<std::chrono::system_clock> nextTimeToLaunch;
    std::chrono::duration<int> frequency;
};

struct MessageComparator {
    bool operator()(const MessagesToLaunch &lhs, const MessagesToLaunch &rhs) const
    {
        return lhs.nextTimeToLaunch < rhs.nextTimeToLaunch;
    }
};

class MessageGeneratorModule : public BaseModule
{
public:
    MessageGeneratorModule(const std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> &outputQueue,
                           const nlohmann::json &config) noexcept;
    ~MessageGeneratorModule() noexcept final;

    bool init() noexcept final;
    void specificStart() noexcept final;
    void update() noexcept final;
    void specificExit() noexcept final;
    std::string_view getModuleName() const noexcept final { return k_moduleName; }

    static constexpr const char *k_moduleName = "MessageGenerator";

private:
    std::set<MessagesToLaunch, MessageComparator> m_messagesToLaunch;
};
}  // namespace core
#endif
