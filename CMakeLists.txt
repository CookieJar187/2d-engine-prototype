cmake_minimum_required(VERSION 3.20)

project(ArmyDefense LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(ArmyDefense
    src/main.cpp
)

target_include_directories(ArmyDefense PRIVATE
    src
)

target_link_libraries(ArmyDefense PRIVATE
    glfw
    glad::glad
)