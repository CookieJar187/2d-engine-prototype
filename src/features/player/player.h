#pragma once

#define MAX_SPEED 200

#include "input.h"
#include "object2.h"
#include "scene.h"
#include "camera2.h"
#include "character_motor2.h"
#include "collision_manager.h"

#include "context.h"

#include "damageable.h"
#include "damage_registry.h"

class Player : Damageable
{
private:
    int health = 100;

    Object2 *body = nullptr;
    Input *input = nullptr;
    Scene *scene = nullptr;
    Camera2 *camera = nullptr;

    CollisionManager *collisionManager = nullptr;
    DamageRegistry *damageRegistry = nullptr;
    BulletSystem *bulletSystem = nullptr;

    CharacterMotor2 characterMotor2;

    void die();

public:
    Player(Context &ctx);
    void update(float deltaTime);
    void takeDamage(float amount) override;
};