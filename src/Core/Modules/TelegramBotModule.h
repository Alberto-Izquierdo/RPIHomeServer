#ifndef TELEGRAMBOTMODULE_H
#define TELEGRAMBOTMODULE_H

#include <Core/BaseModule.h>
#include <nlohmann/json.hpp>

namespace TgBot
{
class Bot;
class TgLongPoll;
class Message;
}  // namespace TgBot

namespace core
{
class TelegramBotModule : public BaseModule
{
public:
    TelegramBotModule(const std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> &outputQueue,
                      const nlohmann::json &config) noexcept;
    ~TelegramBotModule() noexcept final;

    bool init() noexcept final;
    void specificStart() noexcept final;
    void update() noexcept final;
    void specificExit() noexcept final;
    std::string_view getModuleName() const noexcept final { return k_moduleName; }

    void returnAvailableMessages(const std::shared_ptr<Message> &message) noexcept;
    void turnPinOn(std::shared_ptr<TgBot::Message> &message) noexcept;
    void turnPinOff(std::shared_ptr<TgBot::Message> &message) noexcept;
    void turnPinOnAndOff(std::shared_ptr<TgBot::Message> &message) noexcept;
    void welcomeMessage(std::shared_ptr<TgBot::Message> &message) noexcept;

    static constexpr const char *k_moduleName = "TelegramBot";

private:
    bool isUserAuthorized(int userID) const noexcept;
    void handleSpecificMessage(
        std::shared_ptr<TgBot::Message> &message,
        void (TelegramBotModule::*secondaryFunction)(std::shared_ptr<TgBot::Message> &)) noexcept;
    void sendButtons(int64_t messageId, const std::string &messageToShow);

    std::unique_ptr<TgBot::Bot> m_bot;
    std::unique_ptr<TgBot::TgLongPoll> m_longPoll;
    std::vector<std::string> m_userButtons;
    std::vector<uint32_t> m_usersAuthorized;
    int m_networkErrors;
    std::chrono::time_point<std::chrono::system_clock> m_lastNetworkError;
    static const std::chrono::seconds k_timeToSleepBetweenNetworkErrors;
};
}  // namespace core

#endif
