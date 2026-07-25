cmake_minimum_required(VERSION 3.20)

project(ArmyDefense LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(Stb REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(ArmyDefense
    src/main.cpp
    src/core/rendering/texture_loader/texture_loader.cpp
    src/core/camera2/camera2.cpp
    src/core/rendering/mesh_factory/mesh_factory.cpp
    src/core/rendering/shader_loader/shader_loader.cpp
    src/core/world/scene/scene.cpp
    src/core/world/object2/object2.cpp
    src/core/input/input.cpp
    src/core/collision/collision_manager/collision_manager.cpp
    src/core/collision/collision_manager/collision_raycast.cpp
    src/core/collision/collision_manager/collision_registry.cpp
    src/core/collision/character_motor2/character_motor2.cpp

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

target_include_directories(ArmyDefense PRIVATE
    src
    src/core/camera2
    src/core/rendering/texture
    src/core/rendering/texture_loader
    src/core/rendering/material
    src/core/rendering/mesh
    src/core/rendering/mesh_factory
    src/core/rendering/shader
    src/core/rendering/shader_loader
    src/core/world/object2
    src/core/world/scene
    src/core/world/object_creation_result
    src/core/math/transform2
    src/core/input
    src/core/collision/aabb_collider
    src/core/collision/collision_manager
    src/core/collision/collision_entry
    src/core/collision/character_motor2

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

target_link_libraries(ArmyDefense PRIVATE
    glfw
    glad::glad
    glm::glm
    imgui::imgui
    OpenGL::GL
)