#pragma once

#define MAX_SPEED 200

#include "object.h"
#include "scene.h"
#include "character_motor.h"
#include "collision_manager.h"
#include "resource_manager.hpp"

#include "character.hpp"
#include "tilemap.h"
#include "damageable.h"
#include "damage_registry.h"
#include "bullet_system.h"

class Enemy : public Character
{
private:
    Scene *scene;
    ResourceManager *resourceManager;
    Tilemap *tileset;
    BulletSystem *bulletSystem;
    CollisionManager *collisionManager;

    // Ai components
    Object *enemyTarget;

    float maximumForLastTimePathfindingWasUpdated = 1.0f;
    float lastTimePathfindingWasUpdated = 1.0f;

    float maximumForLastTimeGunWasUpdated = 1.0f;
    float lastTimeGunWasUpdated = 1.0f;

    std::vector<glm::ivec2> pathPoints;
    int currPathPoint = 0;
    
public:
    Enemy(   
        Scene &scene,
        DamageRegistry &damageRegistry,
        CollisionManager &collisionManager,
        ResourceManager &resourceManager,
        BulletSystem &bulletSystem,
        Tilemap &tileset,
        glm::vec2 position
    );

    ~Enemy();
    
    void updateAi(float deltaTime);
    void update(float deltaTime);

    void onDamageApplied() override;
    void onDamageStopped() override;
    void onKilled() override;
};