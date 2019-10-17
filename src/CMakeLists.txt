project(iot_project)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(iot_project
    main.cpp)

add_subdirectory(Gpio)
add_subdirectory(Core)
target_link_libraries(iot_project PRIVATE core)

SET(CMAKE_CXX_FLAGS -pthread)
