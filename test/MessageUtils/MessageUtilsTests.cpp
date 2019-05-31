#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include <Core/Communication/MessageUtils.h>

TEST_CASE("MessageUtils", "GetMessageTypesByName")
{
    REQUIRE(core::MessageUtils::getMessageType("asdf") == core::MessageType::NONE);
    REQUIRE(core::MessageUtils::getMessageType("pinOn") == core::MessageType::PIN_ON);
    REQUIRE(core::MessageUtils::getMessageType("pinOff") == core::MessageType::PIN_OFF);
}
