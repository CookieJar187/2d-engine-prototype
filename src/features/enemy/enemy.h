#pragma once

#define MAX_SPEED 200

#include "object2.h"
#include "scene.h"
#include "character_motor2.h"
#include "collision_manager.h"

#include "context.h"

#include "damageable.h"
#include "damage_registry.h"

class Enemy : Damageable
{
private:
    int health = 100;

    Object2 *body = nullptr;
    Scene *scene = nullptr;

    CollisionManager *collisionManager = nullptr;
    DamageRegistry *damageRegistry = nullptr;

    CharacterMotor2 characterMotor2;

    void die();

public:
    Enemy(Context &ctx);
    void update(float deltaTime);
    void takeDamage(float amount) override;
};