#include "character_manager.hpp"

#include <iostream>

CharacterManager::CharacterManager(
    Core &core,
    BulletSystem &bulletSystem,
    DamageRegistry &damageRegistry,
    Tilemap &tilemap,
    GrenadeSystem &grenadeSystem,
    MeleeSystem &meleeSystem,
    CameraShaker &cameraShaker
)
{
    this->scene = &core.scene;
    this->input = &core.input;
    this->camera = &core.camera;
    this->collisionManager = &core.collisionManager;
    this->resourceManager = &core.resourceManager;
    this->bulletSystem = &bulletSystem;
    this->damageRegistry = &damageRegistry;
    this->tilemap = &tilemap;
    this->grenadeSystem = &grenadeSystem;
    this->meleeSystem = &meleeSystem;
    this->cameraShaker = &cameraShaker;
}

void CharacterManager::update(float deltaTime)
{
    // Delete queued for deletion
    if (player.get()->queuedForDeletion)
        player = nullptr;

    for (int i = enemies.size() - 1; i >= 0; i--)
    {
        if (enemies[i].get()->queuedForDeletion)
            enemies.erase(enemies.begin() + i);
    }

    // Update the rest
    if (player != nullptr)
        player.get()->update(deltaTime);

    for (auto &enemy : enemies)
    {
        enemy.get()->update(deltaTime);
    }
}

void CharacterManager::spawnPlayer(glm::vec2 position)
{
    this->player = std::make_unique<Player>(
        *scene,
        *input,
        *camera,
        *collisionManager,
        *resourceManager,
        *bulletSystem,
        *damageRegistry,
        *tilemap,
        *grenadeSystem,
        *meleeSystem,
        *cameraShaker,
        position
    );
}

void CharacterManager::spawnEnemy(glm::vec2 position)
{
    this->enemies.push_back(std::make_unique<Enemy>(
        *scene,
        *damageRegistry,
        *collisionManager,
        *resourceManager,
        *bulletSystem,
        *tilemap,
        position
    ));
}