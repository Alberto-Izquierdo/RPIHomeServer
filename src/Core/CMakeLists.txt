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
    Modules/CommunicationModule.h
    Modules/CommunicationModule.cpp
    Modules/LightModule.h
    Modules/LightModule.cpp
    Modules/TelegramBotModule.h
    Modules/TelegramBotModule.cpp)

target_link_libraries(core PRIVATE ${CONAN_LIBS})
target_link_libraries(core PUBLIC gpio)
