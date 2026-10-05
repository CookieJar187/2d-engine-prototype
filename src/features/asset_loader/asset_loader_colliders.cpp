#include "asset_loader.hpp"

void AssetLoader::loadColliders()
{
    // Colliders
    this->resourceManager->addCollider(
        "friendly_character_collider",
        "character_shape",
        "friendly_character_collision_group"
    );
    this->resourceManager->addCollider(
        "enemy_character_collider",
        "character_shape",
        "enemy_character_collision_group"
    );
    this->resourceManager->addCollider(
        "wall_collider",
        "wall_shape",
        "obstacle_collision_group"
    );
    this->resourceManager->addCollider(
        "boards_horizontal_collider",
        "boards_horizontal_shape",
        "obstacle_collision_group"
    );
    this->resourceManager->addCollider(
        "boards_vertical_collider",
        "boards_vertical_shape",
        "obstacle_collision_group"
    );
    this->resourceManager->addCollider(
        "tree_collider",
        "tree_shape",
        "obstacle_collision_group"
    );
}