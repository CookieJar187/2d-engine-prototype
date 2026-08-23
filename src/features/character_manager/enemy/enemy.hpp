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

class Enemy : public Character
{
private:
    Scene *scene = nullptr;
    ResourceManager *resourceManager = nullptr;
    Tilemap *tileset = nullptr;

    // Ai components
    float maximumForLastTimePathfindingWasUpdated = 1.0f;
    float lastTimePathfindingWasUpdated = 1.0f;

    std::vector<glm::ivec2> pathPoints;
    int currPathPoint = 0;
    
public:
    Enemy(   
        Scene &scene,
        DamageRegistry &damageRegistry,
        CollisionManager &collisionManager,
        ResourceManager &resourceManager,
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