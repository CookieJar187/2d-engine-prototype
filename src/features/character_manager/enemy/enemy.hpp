#pragma once

#define MAX_SPEED 200
#define DAMAGE_EFFECT_DURATION 0.07f
#define DEATH_EFFECT_DURATION 5.0f

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
    ResourceManager *resourceManager = nullptr;
    Tilemap *tileset = nullptr;
    
public:
    Enemy(   
        Scene &scene,
        DamageRegistry &damageRegistry,
        CollisionManager &collisionManager,
        ResourceManager &resourceManager,
        Tilemap &tileset
    );

    ~Enemy();
    
    void update(float deltaTime);

    void onDamageApplied() override;
    void onDamageStopped() override;
    void onKilled() override;
};