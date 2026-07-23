#pragma once

#include "input.h"
#include "object2.h"
#include "scene.h"
#include "character_motor2.h"
#include "collision_manager.h"

class Player
{
private:
    Object2 *body = nullptr;
    Input *input = nullptr;
    Scene *scene = nullptr;
    CollisionManager *collisionManager;

    CharacterMotor2 characterMotor2;

    int maxSpeed = 200;

public:
    void init(Scene &scene, Input &input, CollisionManager &collisionManager);
    void update(float deltaTime);
};