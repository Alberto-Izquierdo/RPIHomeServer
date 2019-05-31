cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(src)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
