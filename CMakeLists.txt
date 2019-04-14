cmake_minimum_required(VERSION 3.7)

project(iot_project)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
 
add_executable(iot_project
    src/main.cpp
    src/Core/BaseModule.h
    src/Core/BaseModule.cpp
    src/Core/MultithreadQueue.h
    src/Core/MultithreadQueue.inl
    src/Core/Communication/MessageTypes.h
    src/Core/Communication/Message.h
    src/Core/Communication/Message.cpp
    src/Core/Communication/MessageDispatcher.h
    src/Core/Communication/MessageDispatcher.cpp
    src/Gpio/GpioController.h
    src/Gpio/GpioController.cpp
    src/Gpio/GpioManager.h
    src/Gpio/GpioManager.cpp)

set_property(TARGET iot_project PROPERTY CXX_STANDARD 14)
