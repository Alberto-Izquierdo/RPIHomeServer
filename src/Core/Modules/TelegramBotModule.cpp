#include "TelegramBotModule.h"
#include <Core/Communication/Message.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreorder"
#include <tgbot/tgbot.h>
#pragma GCC diagnostic pop

#include <thread>
#include <chrono>

using namespace core;

const std::string TelegramBotModule::m_moduleName = "TelegramBot";

TelegramBotModule::TelegramBotModule(std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> &outputQueue) noexcept
    : BaseModule(BaseModule::Type::TELEGRAM_BOT, outputQueue)
    , m_bot(nullptr)
    , m_longPoll(nullptr)
    , m_userButtons({"/lighton", "/lightoff"})
{
}

TelegramBotModule::~TelegramBotModule() noexcept
{
}

bool TelegramBotModule::init() noexcept
{
    // Load bot token
    const char *token = std::getenv("HOME_BOT_TOKEN");
    if (token == NULL) {
        std::cout << "Bot token not set, execute \"export "
                     "HOME_BOT_TOKEN={YOUR_TOKEN}\" before launching the app."
                  << std::endl;
        return false;
    }
    m_bot = std::unique_ptr<TgBot::Bot>(new TgBot::Bot(token));
    m_longPoll = std::unique_ptr<TgBot::TgLongPoll>(new TgBot::TgLongPoll(*m_bot, 100, 5));
    // Load users authorized
    std::ifstream infile("users.txt");
    if (infile.fail()) {
        std::cout
            << "Users file not created, create a file named 'users.txt' with the IDs allowed to use the application"
            << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(infile, line)) {
        std::stringstream iss(line);
        uint32_t userID;
        if (!(iss >> userID)) {
            std::cout << "User ID not correct: " << line << std::endl;
            return false;
        }
        m_usersAuthorized.push_back(userID);
    }
    return true;
}

void TelegramBotModule::specificStart() noexcept
{
    m_bot->getEvents().onCommand("start", [this](TgBot::Message::Ptr message) {
        this->handleSpecificMessage(message, &TelegramBotModule::welcomeMessage);
    });
    m_bot->getEvents().onCommand("lighton", [this](TgBot::Message::Ptr message) {
        this->handleSpecificMessage(message, &TelegramBotModule::turnLightOn);
    });
    m_bot->getEvents().onCommand("lightoff", [this](TgBot::Message::Ptr message) {
        this->handleSpecificMessage(message, &TelegramBotModule::turnLightOff);
    });
}

void TelegramBotModule::update() noexcept
{
    m_longPoll->start();
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

void TelegramBotModule::turnLightOn(std::shared_ptr<TgBot::Message> &message) noexcept
{
    getOutputQueue()->push(std::make_shared<Message>(MessageType::LIGHT_ON));
    sendButtons(message->chat->id, "Light turned on");
}

void TelegramBotModule::turnLightOff(std::shared_ptr<TgBot::Message> &message) noexcept
{
    getOutputQueue()->push(std::make_shared<Message>(MessageType::LIGHT_OFF));
    sendButtons(message->chat->id, "Light turned off");
}

void TelegramBotModule::welcomeMessage(std::shared_ptr<TgBot::Message> &message) noexcept
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
    m_bot->getApi().sendMessage(messageId, messageToShow, false, 0, keyboard);
}

bool TelegramBotModule::isUserAuthorized(uint32_t userID) const noexcept
{
    return std::find(m_usersAuthorized.begin(), m_usersAuthorized.end(), userID) != m_usersAuthorized.end();
}
