#pragma once

#include <vector>
#include <memory>

#include "player.hpp"
#include "enemy.hpp"

#include "scene.h"
#include "input.h"
#include "camera.h"
#include "collision_manager.h"
#include "bullet_system.h"
#include "damage_registry.h"
#include "resource_manager.hpp"
#include "tilemap.h"

class CharacterManager
{
private:
    std::unique_ptr<Player> player = nullptr;

    std::vector<std::unique_ptr<Enemy>> enemies;
    //std::vector<std::unique_ptr<Comrade>> comrades;

    //
    Scene *scene;
    Input *input;
    Camera2 *camera;
    CollisionManager *collisionManager;
    BulletSystem *bulletSystem;
    DamageRegistry *damageRegistry;
    ResourceManager *resourceManager;
    Tilemap *tilemap;

public:
    CharacterManager(
        Scene &scene,
        Input &input,
        Camera2 &camera,
        CollisionManager &collisionManager,
        BulletSystem &bulletSystem,
        DamageRegistry &damageRegistry,
        ResourceManager &resourceManager,
        Tilemap &tilemap
    );

    void update(float deltaTime);

    void spawnPlayer();
    void spawnEnemy();
    void spawnComrade();

    void despawnPlayer();
    void despawnEnemies();
    void despawnComrades();

    void despawnEverybody();

};