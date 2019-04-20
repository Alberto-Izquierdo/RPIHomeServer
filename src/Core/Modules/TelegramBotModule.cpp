#include "TelegramBotModule.h"
#include <Core/Communication/Message.h>
#include <thread>
#include <chrono>

using namespace core;

const std::string TelegramBotModule::m_moduleName = "TelegramBot";

TelegramBotModule::TelegramBotModule(std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> &outputQueue) noexcept
    : BaseModule(BaseModule::Type::TELEGRAM_BOT, outputQueue)
{
}

TelegramBotModule::~TelegramBotModule() noexcept
{
}

void TelegramBotModule::specificStart() noexcept
{
}

void TelegramBotModule::update() noexcept
{
    // TODO: Poll telegram server
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

void TelegramBotModule::turnOnLight() noexcept
{
    getOutputQueue()->push(std::make_shared<Message>(MessageType::LIGHT_ON));
}

void TelegramBotModule::turnOffLight() noexcept
{
    getOutputQueue()->push(std::make_shared<Message>(MessageType::LIGHT_OFF));
}
