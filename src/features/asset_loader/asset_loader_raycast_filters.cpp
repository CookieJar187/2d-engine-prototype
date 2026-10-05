#include "asset_loader.hpp"

void AssetLoader::loadRaycastFilters()
{
    // Raycast filters
    this->resourceManager->addRaycastFilter(
        "grenade_raycast_filter",
        RaycastFilterMode::PermitOnly
    );
    this->resourceManager->addRaycastFilter(
        "friendly_bullet_raycast_filter",
        RaycastFilterMode::Ignore
    );
    this->resourceManager->addRaycastFilter(
        "enemy_bullet_raycast_filter",
        RaycastFilterMode::Ignore
    );

    this->resourceManager->setRaycastFilterGroup(
        "grenade_raycast_filter",
        "obstacle_collision_group"
    );
    this->resourceManager->setRaycastFilterGroup(
        "friendly_bullet_raycast_filter",
        "friendly_character_collision_group"
    );
    this->resourceManager->setRaycastFilterGroup(
        "enemy_bullet_raycast_filter",
        "enemy_character_collision_group"
    );
}