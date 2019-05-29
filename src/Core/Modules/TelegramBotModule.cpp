#include "TelegramBotModule.h"
#include <Core/Communication/Message.h>
#include <Core/Communication/Messages/ReturnAvailablePinsMessage.h>
#include <Core/Communication/Messages/GetAvailablePinsMessage.h>
#include <Core/Communication/Messages/PinOnMessage.h>
#include <Core/Communication/Messages/PinOffMessage.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreorder"
#include <tgbot/tgbot.h>
#pragma GCC diagnostic pop

#include <thread>
#include <chrono>
#include <algorithm>

using namespace core;

const std::string TelegramBotModule::k_moduleName = "TelegramBot";

TelegramBotModule::TelegramBotModule(std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> &outputQueue,
                                     const nlohmann::json &config) noexcept
    : BaseModule(BaseModule::Type::TELEGRAM_BOT, outputQueue)
    , m_bot(nullptr)
    , m_longPoll(nullptr)
{
    // Load users authorized
    auto users = config.find("users");
    if (users != config.end()) {
        if (users->is_array()) {
            for (auto it = users->begin(); it != users->end(); ++it) {
                if (it->is_number()) {
                    m_usersAuthorized.emplace_back(it.value());
                } else {
                    std::cout << "User " << it.value() << " not well defined (should be a number)" << std::endl;
                }
            }
        }
    }
    if (m_usersAuthorized.empty()) {
        std::cout << "No users added to telegram bot" << std::endl;
    }
    auto token = config.find("token");
    if (token != config.end()) {
        if (token->is_string()) {
            auto botPtr = new TgBot::Bot(token.value());
            m_bot = std::unique_ptr<TgBot::Bot>(botPtr);
        }
    }
    addMessageHandler(
        core::MessageType::RETURN_AVAILABLE_PIN_ALIASES,
        reinterpret_cast<BaseModule::messageHanlderFunction>(&TelegramBotModule::returnAvailableMessages));
}

TelegramBotModule::~TelegramBotModule() noexcept
{
}

bool TelegramBotModule::init() noexcept
{
    // Load bot token
    if (m_bot == nullptr) {
        std::cout << "Bot token not set or it is not correct, add the field \"token\" to the config file and set the "
                     "token provided by the Botfather."
                  << std::endl;
        return false;
    }
    m_longPoll = std::unique_ptr<TgBot::TgLongPoll>(new TgBot::TgLongPoll(*m_bot, 100, 5));
    return true;
}

void TelegramBotModule::specificStart() noexcept
{
    m_bot->getEvents().onCommand("start", [this](TgBot::Message::Ptr message) {
        this->handleSpecificMessage(message, &TelegramBotModule::welcomeMessage);
    });
}

void TelegramBotModule::update() noexcept
{
    m_longPoll->start();
    getInputQueue()->waitForPushIfEmpty(2);
    while (!getInputQueue()->isEmpty()) {
        std::shared_ptr<Message> message;
        if (getInputQueue()->front(message)) {
            handleMessage(message);
        }
    }
}

void TelegramBotModule::specificExit() noexcept
{
}

void TelegramBotModule::handleSpecificMessage(
    std::shared_ptr<TgBot::Message> &message,
    void (TelegramBotModule::*secondaryFunction)(std::shared_ptr<TgBot::Message> &)) noexcept
{
    if (isUserAuthorized(message->from->id)) {
        (this->*secondaryFunction)(message);
    } else {
        m_bot->getApi().sendMessage(message->chat->id, "User not authorized :(");
        std::cout << "User " << message->from->id << " tried to send a message" << std::endl;
    }
}

void TelegramBotModule::returnAvailableMessages(const std::shared_ptr<Message> message) noexcept
{
    auto castedMessage = std::static_pointer_cast<ReturnAvailablePinsMessage>(message);
    const auto &pinsAvailable = castedMessage->getPinsAvailable();
    m_userButtons.clear();
    std::for_each(pinsAvailable.begin(), pinsAvailable.end(), [&](const std::string &pin) -> void {
        std::string onName = pin + "On";
        std::string offName = pin + "Off";
        m_bot->getEvents().onCommand(onName, [this, pin](TgBot::Message::Ptr message) {
            this->handleSpecificMessage(message, &TelegramBotModule::turnPinOn);
        });
        m_bot->getEvents().onCommand(offName, [this, pin](TgBot::Message::Ptr message) {
            this->handleSpecificMessage(message, &TelegramBotModule::turnPinOff);
        });
        m_userButtons.emplace_back("/" + onName);
        m_userButtons.emplace_back("/" + offName);
    });
    sendButtons(castedMessage->getChatId(), "Welcome, please select an option");
}

void TelegramBotModule::turnPinOn(std::shared_ptr<TgBot::Message> &message) noexcept
{
    const auto &fullMessage = message->text;
    auto pin = fullMessage.substr(1, fullMessage.size() - 3);
    getOutputQueue()->push(std::make_shared<PinOnMessage>(pin));
    sendButtons(message->chat->id, "Pin " + pin + " turned on");
}

void TelegramBotModule::turnPinOff(std::shared_ptr<TgBot::Message> &message) noexcept
{
    const auto &fullMessage = message->text;
    auto pin = fullMessage.substr(1, fullMessage.size() - 4);
    getOutputQueue()->push(std::make_shared<PinOffMessage>(pin));
    sendButtons(message->chat->id, "Pin " + pin + " turned off");
}

void TelegramBotModule::welcomeMessage(std::shared_ptr<TgBot::Message> &message) noexcept
{
    getOutputQueue()->push(std::make_shared<GetAvailablePinsMessage>(message->chat->id));
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
    m_bot->getApi().sendMessage(messageId, messageToShow, false, 0, keyboard);
}

bool TelegramBotModule::isUserAuthorized(int userID) const noexcept
{
    return std::find(m_usersAuthorized.begin(), m_usersAuthorized.end(), userID) != m_usersAuthorized.end();
}
