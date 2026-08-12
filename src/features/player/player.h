#pragma once

#define MAX_SPEED 200

#include "input.h"
#include "object.h"
#include "scene.h"
#include "camera.h"
#include "character_motor.h"
#include "collision_manager.h"

#include "context.h"

#include "damageable.h"
#include "damage_registry.h"

class Player : Damageable
{
private:
    int health = 100;

    Object *body = nullptr;
    Input *input = nullptr;
    Scene *scene = nullptr;
    Camera2 *camera = nullptr;

    CollisionManager *collisionManager = nullptr;
    DamageRegistry *damageRegistry = nullptr;
    BulletSystem *bulletSystem = nullptr;

    CharacterMotor CharacterMotor;

    void die();

public:
    Player(Context &ctx);
    void update(float deltaTime);
    void takeDamage(float amount) override;
};