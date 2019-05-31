cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(src)

include(${CMAKE_CURRENT_SOURCE_DIR}/conan.cmake)

if ("${CMAKE_CXX_COMPILER}" MATCHES "arm")
conan_cmake_run(CONANFILE conanfile.txt
                PROFILE ../rpi_profile
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)
else ("${CMAKE_CXX_COMPILER}" MATCHES "arm")
conan_cmake_run(CONANFILE conanfile.txt
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)
endif ("${CMAKE_CXX_COMPILER}" MATCHES "arm")

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
