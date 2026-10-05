#include "asset_loader.hpp"

void AssetLoader::loadCollisionGroups()
{
    // Collision groups
    this->resourceManager->addCollisionGroup(
        "friendly_character_collision_group"
    );
    this->resourceManager->addCollisionGroup(
        "enemy_character_collision_group"
    );
    this->resourceManager->addCollisionGroup(
        "obstacle_collision_group"
    );
    
    this->resourceManager->setCollisionGroupRelationship(
        "friendly_character_collision_group",
        "obstacle_collision_group"
    );
    this->resourceManager->setCollisionGroupRelationship(
        "enemy_character_collision_group",
        "obstacle_collision_group"
    );
}