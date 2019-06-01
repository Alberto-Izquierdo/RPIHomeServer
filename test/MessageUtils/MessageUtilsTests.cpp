#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include <Core/Communication/MessageUtils.h>
#include <Core/Communication/Messages/MessageFactory.h>
#include <Core/Communication/Messages/PinOnMessage.h>
#include <Core/Communication/Messages/PinOffMessage.h>

TEST_CASE("MessageUtils", "GetMessageTypesByName")
{
    REQUIRE(core::MessageUtils::getMessageType("asdf") == core::MessageType::NONE);
    REQUIRE(core::MessageUtils::getMessageType("pinOn") == core::MessageType::PIN_ON);
    REQUIRE(core::MessageUtils::getMessageType("pinOff") == core::MessageType::PIN_OFF);

    REQUIRE(core::MessageUtils::getMessageTypeName(core::MessageType::PIN_ON) == "pinOn");
    REQUIRE(core::MessageUtils::getMessageTypeName(core::MessageType::PIN_OFF) == "pinOff");
}

TEST_CASE("MessageFactory", "CreateMessageByJson")
{
    nlohmann::json pinOn = "{ \"pinOn\": { \"alias\": \"light\" } }"_json;
    auto pinOnMessage = core::MessageFactory::makeMessage(pinOn);
    REQUIRE(dynamic_cast<core::PinOnMessage *>(pinOnMessage.get()));
    REQUIRE(std::static_pointer_cast<core::PinOnMessage>(pinOnMessage)->getPinAlias() == "light");

    nlohmann::json pinOff = "{ \"pinOff\": { \"alias\": \"light\" } }"_json;
    auto pinOffMessage = core::MessageFactory::makeMessage(pinOff);
    REQUIRE(dynamic_cast<core::PinOffMessage *>(pinOffMessage.get()));
    REQUIRE(std::static_pointer_cast<core::PinOffMessage>(pinOffMessage)->getPinAlias() == "light");

    nlohmann::json typo1 = "{ \"pinOnf\": { \"alias\": \"light\" } }"_json;
    auto typo1Message = core::MessageFactory::makeMessage(typo1);
    REQUIRE(typo1Message == nullptr);

    nlohmann::json typo2 = "{ \"pinOff\": { \"aleas\": \"light\" } }"_json;
    auto typo2Message = core::MessageFactory::makeMessage(typo2);
    REQUIRE(typo2Message == nullptr);
}
