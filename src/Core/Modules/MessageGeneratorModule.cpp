#include "MessageGeneratorModule.h"
#include <Core/Communication/Messages/MessageFactory.h>
#include <Core/Communication/MessageUtils.h>
#include <thread>
#include <iostream>

using namespace core;

MessageGeneratorModule::MessageGeneratorModule(
    const std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> &outputQueue,
    const nlohmann::json &config) noexcept
    : BaseModule(BaseModule::Type::MESSAGE_GENERATOR, outputQueue)
{
    auto messages = config.find("messages");
    if (messages != config.end() && messages.value().is_array()) {
        for (auto it : messages.value()) {
            auto messageJson = it.find("message");
            auto timeJson = it.find("time");
            if (messageJson != it.end() && messageJson.value().is_object() && timeJson != it.end() &&
                timeJson.value().is_string()) {
                auto message = MessageFactory::makeMessage(messageJson.value());
                auto time = MessageUtils::getTimeFromString(timeJson.value());
                if (message != nullptr || time > std::chrono::system_clock::now()) {
                    m_messagesToLaunch.emplace(message, std::move(time), std::chrono::hours(24));
                } else {
                    if (message == nullptr) {
                        std::cout << "Message not well defined" << std::endl;
                    }
                    if (time < std::chrono::system_clock::now()) {
                        std::cout << "Time not well set" << std::endl;
                    }
                }
            } else {
                if (messageJson == it.end() || !messageJson.value().is_object()) {
                    std::cout << "Message not found or not well defined" << std::endl;
                }
                if (timeJson == it.end() || !timeJson.value().is_string()) {
                    std::cout << "Time not found or not well defined" << std::endl;
                }
            }
        }
    }
}

MessageGeneratorModule::~MessageGeneratorModule() noexcept
{
}

bool MessageGeneratorModule::init() noexcept
{
    if (m_messagesToLaunch.empty()) {
        return false;
    }
    return true;
}

void MessageGeneratorModule::specificStart() noexcept
{
}

void MessageGeneratorModule::update() noexcept
{
    auto messageToLaunch = m_messagesToLaunch.begin();
    auto inputQueue = getInputQueue();
    inputQueue->waitForPushIfEmpty(messageToLaunch->nextTimeToLaunch);
    if (inputQueue->isEmpty()) {
        auto message = messageToLaunch->message;
        getOutputQueue()->push(message);
        auto frequency = messageToLaunch->frequency;
        auto nextTime = messageToLaunch->nextTimeToLaunch + frequency;
        m_messagesToLaunch.erase(messageToLaunch);
        m_messagesToLaunch.emplace(message, std::move(nextTime), std::move(frequency));
    } else {
        std::shared_ptr<Message> message;
        if (inputQueue->front(message)) {
            handleMessage(message);
        }
    }
}

void MessageGeneratorModule::specificExit() noexcept
{
}
