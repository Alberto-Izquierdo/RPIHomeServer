# Define our host system
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)

SET(CMAKE_C_COMPILER arm-linux-gnueabi-gcc-8)
SET(CMAKE_CXX_COMPILER arm-linux-gnueabi-g++-8)

add_definitions(-Wall -std=c++17)
