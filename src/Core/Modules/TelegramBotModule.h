#ifndef TELEGRAMBOTMODULE_H
#define TELEGRAMBOTMODULE_H

#include <Core/BaseModule.h>
#include <tgbot/tgbot.h>

namespace core
{
class TelegramBotModule : public BaseModule
{
public:
    TelegramBotModule(const char *token,
                      std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> &outputQueue) noexcept;
    ~TelegramBotModule() noexcept final;

    void specificStart() noexcept final;
    void update() noexcept final;
    void specificExit() noexcept final;
    const std::string &getModuleName() const noexcept final;

    void turnLightOn(TgBot::Message::Ptr message) noexcept;
    void turnLightOff(TgBot::Message::Ptr message) noexcept;
    void welcomeMessage(TgBot::Message::Ptr message) noexcept;

private:
    void sendButtons(int64_t messageId, const std::string &messageToShow);

    static const std::string m_moduleName;
    TgBot::Bot m_bot;
    TgBot::TgLongPoll m_longPoll;
    std::vector<std::string> m_userButtons;
};
}  // namespace core

#endif
