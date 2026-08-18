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
    src/core/resource_manager/resource_manager.cpp
    src/core/loaders/mesh_loader/mesh_loader.cpp
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

    src/features/character_manager/character_manager.cpp
    src/features/character_manager/player/player.cpp
    src/features/character_manager/enemy/enemy.cpp
    src/features/character_manager/enemy/enemy_damage.cpp
    src/features/game_assets/game_assets.cpp
    src/features/tilemap/tilemap.cpp
    src/features/damage/damage_registry.cpp
    src/features/bullet_system/bullet_system.cpp
    src/features/pathfinding/pathfinding.cpp
)

target_include_directories(2DEnginePrototype PRIVATE
    src
    src/core/resource_manager
    src/core/loaders/mesh_loader
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

    src/features/game_assets
    src/features/character_manager
    src/features/character_manager/player
    src/features/character_manager/enemy
    src/features/tilemap
    src/features/damage
    src/features/bullet_system
    src/features/pathfinding

    ${Stb_INCLUDE_DIR}
)

target_link_libraries(2DEnginePrototype PRIVATE
    glfw
    glad::glad
    glm::glm
    imgui::imgui
    OpenGL::GL
)