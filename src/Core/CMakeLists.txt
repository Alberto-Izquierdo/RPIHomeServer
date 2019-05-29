add_library(core
    App.h
    App.cpp
    BaseModule.h
    BaseModule.cpp
    MultithreadQueue.h
    MultithreadQueue.inl
    Communication/MessageTypes.h
    Communication/Message.h
    Communication/Message.cpp
    Communication/MessageDispatcher.h
    Communication/MessageDispatcher.cpp
    Communication/Messages/PinOnMessage.h
    Communication/Messages/PinOnMessage.cpp
    Communication/Messages/PinOffMessage.h
    Communication/Messages/PinOffMessage.cpp
    Communication/Messages/GetAvailablePinsMessage.h
    Communication/Messages/GetAvailablePinsMessage.cpp
    Communication/Messages/ReturnAvailablePinsMessage.h
    Communication/Messages/ReturnAvailablePinsMessage.cpp
    Modules/CommunicationModule.h
    Modules/CommunicationModule.cpp
    Modules/GPIOModule.h
    Modules/GPIOModule.cpp
    Modules/TelegramBotModule.h
    Modules/TelegramBotModule.cpp)

target_link_libraries(core PRIVATE ${CONAN_LIBS})
target_link_libraries(core PUBLIC gpio)
