#ifndef MESSAGETYPES_H
#define MESSAGETYPES_H

namespace core
{
enum MessageType {
    EXIT,
    PIN_ON,
    PIN_OFF,
    PIN_ON_AND_OFF,
    GET_AVAILABLE_PIN_ALIASES,
    RETURN_AVAILABLE_PIN_ALIASES,
    NONE
};
}  // namespace core

#endif
