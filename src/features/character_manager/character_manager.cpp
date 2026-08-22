#include "character_manager.hpp"

#include <iostream>

CharacterManager::CharacterManager(
    Scene &scene,
    Input &input,
    Camera2 &camera,
    CollisionManager &collisionManager,
    BulletSystem &bulletSystem,
    DamageRegistry &damageRegistry,
    ResourceManager &resourceManager,
    Tilemap &tilemap
)
{
    this->scene = &scene;
    this->input = &input;
    this->camera = &camera;
    this->collisionManager = &collisionManager;
    this->bulletSystem = &bulletSystem;
    this->damageRegistry = &damageRegistry;
    this->resourceManager = &resourceManager;
    this->tilemap = &tilemap;
}

void CharacterManager::update(float deltaTime)
{
    // Delete queued for deletion
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

void CharacterManager::spawnPlayer()
{
    this->player = std::make_unique<Player>(
        *scene,
        *input,
        *camera,
        *collisionManager,
        *bulletSystem,
        *damageRegistry,
        *tilemap
    );
}

void CharacterManager::spawnEnemy()
{
    this->enemies.push_back(std::make_unique<Enemy>(
        *scene,
        *damageRegistry,
        *collisionManager,
        *resourceManager,
        *tilemap
    ));
}