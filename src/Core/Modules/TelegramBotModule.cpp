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
    , m_userButtons({"/lighton", "/lightoff"})
{
}

TelegramBotModule::~TelegramBotModule() noexcept
{
}

void TelegramBotModule::specificStart() noexcept
{
    m_bot.getEvents().onCommand("start", [this](TgBot::Message::Ptr message) { this->welcomeMessage(message); });
    m_bot.getEvents().onCommand("lighton", [this](TgBot::Message::Ptr message) { this->turnLightOn(message); });
    m_bot.getEvents().onCommand("lightoff", [this](TgBot::Message::Ptr message) { this->turnLightOff(message); });
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

void TelegramBotModule::turnLightOn(TgBot::Message::Ptr message) noexcept
{
    getOutputQueue()->push(std::make_shared<Message>(MessageType::LIGHT_ON));
    sendButtons(message->chat->id, "Light turned on");
}

void TelegramBotModule::turnLightOff(TgBot::Message::Ptr message) noexcept
{
    getOutputQueue()->push(std::make_shared<Message>(MessageType::LIGHT_OFF));
    sendButtons(message->chat->id, "Light turned off");
}

void TelegramBotModule::welcomeMessage(TgBot::Message::Ptr message) noexcept
{
    sendButtons(message->chat->id, "Welcome, please select an option");
}

void TelegramBotModule::sendButtons(int64_t messageId, const std::string &messageToShow)
{
    TgBot::ReplyKeyboardMarkup::Ptr keyboard(new TgBot::ReplyKeyboardMarkup());
    keyboard->oneTimeKeyboard = false;
    std::vector<TgBot::KeyboardButton::Ptr> row;
    for (const auto &option : m_userButtons) {
        TgBot::KeyboardButton::Ptr button(new TgBot::KeyboardButton);
        button->text = option;
        row.push_back(button);
    }
    keyboard->keyboard.push_back(row);
    m_bot.getApi().sendMessage(messageId, messageToShow, false, 0, keyboard);
}
