cmake_minimum_required(VERSION 3.13)

project(iot_project)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
 
add_executable(iot_project
    src/main.cpp
    src/Gpio/GpioController.h
    src/Gpio/GpioController.cpp
    src/Gpio/GpioManager.h
    src/Gpio/GpioManager.cpp)

target_compile_features(iot_project PRIVATE cxx_std_17)

