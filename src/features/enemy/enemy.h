#pragma once

#define MAX_SPEED 200

#include "object.h"
#include "scene.h"
#include "character_motor.h"
#include "collision_manager.h"

#include "damageable.h"
#include "damage_registry.h"

class Enemy : Damageable
{
private:
    int health = 100;

    Object *body = nullptr;
    Scene *scene = nullptr;

    CollisionManager *collisionManager = nullptr;
    DamageRegistry *damageRegistry = nullptr;

    CharacterMotor CharacterMotor;

    void die();

public:
    Enemy(   
        Scene &scene,
        DamageRegistry &damageRegistry,
        CollisionManager &collisionManager
    );
    
    void update(float deltaTime);
    void takeDamage(float amount) override;
};