#pragma once

#define MAX_SPEED 200

#include "core.hpp"

#include "character.hpp"
#include "tilemap.h"
#include "damageable.h"
#include "damage_registry.h"
#include "bullet_system.h"

class Comrade : public Character
{
private:
    Scene *scene;
    ResourceManager *resourceManager;
    Tilemap *tileset;
    BulletSystem *bulletSystem;
    Collision *collision;

    // Ai components
    Object *enemyTarget;

    float maximumForLastTimePathfindingWasUpdated = 1.0f;
    float lastTimePathfindingWasUpdated = 1.0f;

    float maximumForLastTimeGunWasUpdated = 1.0f;
    float lastTimeGunWasUpdated = 1.0f;

    std::vector<glm::ivec2> pathPoints;
    int currPathPoint = 0;

    Object *getClosestEnemy(Scene &scene);
    
public:
    Comrade(   
        Core &core,
        DamageRegistry &damageRegistry,
        BulletSystem &bulletSystem,
        Tilemap &tileset,
        glm::vec2 position
    );

    ~Comrade();
    
    void updateAi(float deltaTime);
    void update(float deltaTime);

    void onDamageApplied() override;
    void onDamageStopped() override;
    void onKilled() override;
};