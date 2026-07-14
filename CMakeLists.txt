cmake_minimum_required(VERSION 3.20)

project(ArmyDefense LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(ArmyDefense
    
    src/core/scene/scene.cpp
    src/core/mesh_factory/mesh_factory.cpp
    src/core/object2/object2.cpp
    src/core/shader_loader/shader_loader.cpp
    src/main.cpp
)

target_include_directories(ArmyDefense PRIVATE
    src
    src/core/camera2
    src/core/material
    src/core/mesh
    src/core/mesh_factory
    src/core/object2
    src/core/scene
    src/core/shader
    src/core/shader_loader
    src/core/math/transform2
    src/core/math/vector2
)

target_link_libraries(ArmyDefense PRIVATE
    glfw
    glad::glad
    glm::glm
)