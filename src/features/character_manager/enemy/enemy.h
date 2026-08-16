#pragma once

#define MAX_SPEED 200
#define DAMAGE_EFFECT_DURATION 0.07f
#define DEATH_EFFECT_DURATION 5.0f

#include "object.h"
#include "scene.h"
#include "character_motor.h"
#include "collision_manager.h"
#include "resource_manager.hpp"

#include "tilemap.h"
#include "damageable.h"
#include "damage_registry.h"

class Enemy : Damageable
{
private:
    Scene *scene = nullptr;
    DamageRegistry *damageRegistry = nullptr;
    CollisionManager *collisionManager = nullptr;
    ResourceManager *resourceManager = nullptr;
    Tilemap *tileset = nullptr;

    Object *body = nullptr;
    CharacterMotor CharacterMotor;

    int health = 100;
    bool dead = false;

    float damageEffectElapsed = 0.0f;
    float deathEffectElapsed = 0.0f;
    bool damageEffect = false;

    void death();
    void updateDamage(float deltaTime);

public:
    Enemy(   
        Scene &scene,
        DamageRegistry &damageRegistry,
        CollisionManager &collisionManager,
        ResourceManager &resourceManager,
        Tilemap &tileset
    );
    
    void update(float deltaTime);
    void takeDamage(float amount) override;
};