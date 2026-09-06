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
    this->core = &core;
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

    for (int i = comrades.size() - 1; i >= 0; i--)
    {
        if (comrades[i].get()->queuedForDeletion)
            comrades.erase(comrades.begin() + i);
    }

    // Update the rest
    if (player != nullptr)
        player.get()->update(deltaTime);

    for (auto &enemy : enemies)
    {
        enemy.get()->update(deltaTime);
    }

    for (auto &comrade : comrades)
    {
        comrade.get()->update(deltaTime);
    }
}

void CharacterManager::spawnPlayer(glm::vec2 position)
{
    this->player = std::make_unique<Player>(
        *core,
        *damageRegistry,
        *bulletSystem,
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
        *core,
        *damageRegistry,
        *bulletSystem,
        *tilemap,
        position
    ));
}

void CharacterManager::spawnComrade(glm::vec2 position)
{
    this->comrades.push_back(std::make_unique<Comrade>(
        *core,
        *damageRegistry,
        *bulletSystem,
        *tilemap,
        position
    ));
}