#pragma once

#include <vector>
#include <memory>
#include <optional>

#include "core.hpp"

#include "player.hpp"
#include "enemy.hpp"
#include "comrade.hpp"

#include "bullet_system.h"
#include "damage_registry.h"
#include "tilemap.h"
#include "grenade_system.hpp"
#include "melee_system.hpp"
#include "camera_shaker.hpp"

class CharacterManager
{
private:
    std::unique_ptr<Player> player = nullptr;

    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Comrade>> comrades;

    //
    Core *core;

    BulletSystem *bulletSystem;
    DamageRegistry *damageRegistry;
    Tilemap *tilemap;
    GrenadeSystem *grenadeSystem;
    MeleeSystem *meleeSystem;
    CameraShaker *cameraShaker;

public:
    CharacterManager(
        Core &core,
        BulletSystem &bulletSystem,
        DamageRegistry &damageRegistry,
        Tilemap &tilemap,
        GrenadeSystem &grenadeSystem,
        MeleeSystem &meleeSystem,
        CameraShaker &cameraShaker
    );

    void update(float deltaTime);

    void spawnPlayer(glm::vec2 position = {0, 0});
    void spawnEnemy(glm::vec2 position = {0, 0});
    void spawnComrade(glm::vec2 position = {0, 0});

    void despawnPlayer();
    void despawnEnemies();
    void despawnComrades();

    void despawnEverybody();

};