#include "TelegramBotModule.h"
#include <Core/Communication/Message.h>
#include <thread>
#include <chrono>

using namespace core;

const std::string TelegramBotModule::m_moduleName = "TelegramBot";

TelegramBotModule::TelegramBotModule(const char *token,
                                     std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> &outputQueue) noexcept
    : BaseModule(BaseModule::Type::TELEGRAM_BOT, outputQueue)
    , m_bot(token)
    , m_longPoll(m_bot, 100, 5)
{
}

TelegramBotModule::~TelegramBotModule() noexcept
{
}

void TelegramBotModule::specificStart() noexcept
{
    m_bot.getEvents().onCommand("start", [this](TgBot::Message::Ptr message) { this->welcomeMessage(); });
    m_bot.getEvents().onCommand("lighton", [this](TgBot::Message::Ptr message) { this->turnLightOn(); });
    m_bot.getEvents().onCommand("lightoff", [this](TgBot::Message::Ptr message) { this->turnLightOff(); });
}

void TelegramBotModule::update() noexcept
{
    m_longPoll.start();
    getInputQueue()->waitForPushIfEmpty(2);
    while (!getInputQueue()->isEmpty()) {
        handleMessage(getInputQueue()->front());
        getInputQueue()->pop();
    }
}

void TelegramBotModule::specificExit() noexcept
{
}

const std::string &TelegramBotModule::getModuleName() const noexcept
{
    return m_moduleName;
}

void TelegramBotModule::turnLightOn() noexcept
{
    getOutputQueue()->push(std::make_shared<Message>(MessageType::LIGHT_ON));
}

void TelegramBotModule::turnLightOff() noexcept
{
    getOutputQueue()->push(std::make_shared<Message>(MessageType::LIGHT_OFF));
}

void TelegramBotModule::welcomeMessage() noexcept
{
    // TODO: send options to user
}
