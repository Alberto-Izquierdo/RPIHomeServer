find_package(Protobuf REQUIRED)

EXEC_PROGRAM(${PROTOBUF_PROTOC_EXECUTABLE} ARGS -I ${CMAKE_SOURCE_DIR}/protobuf_messages/ --grpc_out=${CMAKE_CURRENT_BINARY_DIR}/ --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ${CMAKE_SOURCE_DIR}/protobuf_messages/messages.proto)
EXEC_PROGRAM(${PROTOBUF_PROTOC_EXECUTABLE} ARGS -I ${CMAKE_SOURCE_DIR}/protobuf_messages/ --cpp_out=${CMAKE_CURRENT_BINARY_DIR}/ ${CMAKE_SOURCE_DIR}/protobuf_messages/messages.proto)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

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
    Communication/MessageUtils.h
    Communication/MessageUtils.cpp
    Communication/Messages/PinOnMessage.h
    Communication/Messages/PinOnMessage.cpp
    Communication/Messages/PinOffMessage.h
    Communication/Messages/PinOffMessage.cpp
    Communication/Messages/PinOnAndOffMessage.h
    Communication/Messages/PinOnAndOffMessage.cpp
    Communication/Messages/GetAvailablePinsMessage.h
    Communication/Messages/GetAvailablePinsMessage.cpp
    Communication/Messages/ReturnAvailablePinsMessage.h
    Communication/Messages/ReturnAvailablePinsMessage.cpp
    Communication/Messages/MessageFactory.h
    Communication/Messages/MessageFactory.cpp
    Modules/CommunicationModule.h
    Modules/CommunicationModule.cpp
    Modules/GPIOModule.h
    Modules/GPIOModule.cpp
    Modules/TelegramBotModule.h
    Modules/TelegramBotModule.cpp
    Modules/MessageGeneratorModule.h
    Modules/MessageGeneratorModule.cpp
    gRPC/GRPCServer.h
    gRPC/GRPCServer.cpp
    ${PROTO_HDRS}
    ${PROTO_SRCS})

target_link_libraries(core PRIVATE gpio CONAN_PKG::jsonformoderncpp CONAN_PKG::tgbot_cpp CONAN_PKG::protobuf CONAN_PKG::grpc)
