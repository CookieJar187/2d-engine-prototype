cmake_minimum_required(VERSION 3.20)

project(2DEnginePrototype LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(Stb REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(2DEnginePrototype
    src/main.cpp
    src/core/mesh_factory/mesh_factory.cpp
    src/core/loaders/texture_loader/texture_loader.cpp
    src/core/loaders/shader_loader/shader_loader.cpp
    src/core/world/camera/camera.cpp
    src/core/world/scene/scene.cpp
    src/core/world/object/object.cpp
    src/core/world/collision/collision_manager/collision_manager.cpp
    src/core/world/collision/collision_manager/collision_raycast.cpp
    src/core/world/collision/character_motor/character_motor.cpp
    src/core/input/input.cpp

    src/game_fsm/game_fsm.cpp

    src/ui/ui_manager/ui_manager.cpp
    src/ui/screens/main_menu/main_menu.cpp
    src/ui/screens/settings/settings.cpp
    src/ui/screens/level_selection/level_selection.cpp

    src/features/player/player.cpp
    src/features/enemy/enemy.cpp
    src/features/tilemap/tilemap.cpp
    src/features/damage/damage_registry.cpp
    src/features/bullet_system/bullet_system.cpp

    src/asset_library/asset_library.cpp
)

target_include_directories(2DEnginePrototype PRIVATE
    src
    src/core/mesh_factory
    src/core/loaders/texture_loader
    src/core/loaders/shader_loader
    src/core/world/camera
    src/core/world
    src/core/world/object
    src/core/world/object/rendering/material
    src/core/world/object/rendering/mesh
    src/core/world/object/rendering/shader
    src/core/world/object/rendering/texture
    src/core/world/scene
    src/core/world/object_creation_result
    src/core/math/transform2
    src/core/world/collision/collision_manager
    src/core/world/collision/aabb_collider
    src/core/world/collision/character_motor
    src/core/input

    src/game_fsm

    src/ui/ui_manager
    src/ui/screens/main_menu
    src/ui/screens/settings
    src/ui/screens/level_selection

    src/features/player
    src/features/enemy
    src/features/tilemap
    src/features/damage
    src/features/bullet_system

    src/asset_library

    src/context

    ${Stb_INCLUDE_DIR}
)

target_link_libraries(2DEnginePrototype PRIVATE
    glfw
    glad::glad
    glm::glm
    imgui::imgui
    OpenGL::GL
)