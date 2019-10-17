# Define our host system
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)


SET(CMAKE_C_COMPILER arm-linux-gnueabi-gcc-8)
SET(CMAKE_CXX_COMPILER arm-linux-gnueabi-g++-8)
#SET(CMAKE_FIND_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR}/tools/arm-bcm2708/arm-linux-gnueabihf/arm-linux-gnueabihf/sysroot/)

# Use our definitions for compiler tools
# SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# Search for libraries and headers in the target directories only
# SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
SET(CMAKE_BUILD_TYPE Release)

add_definitions(-Wall -std=c++17)
