#pragma once

#define MAX_SPEED 200

#include "input.h"
#include "object2.h"
#include "scene.h"
#include "camera2.h"
#include "character_motor2.h"
#include "collision_manager.h"

class Player
{
private:
    Object2 *body = nullptr;
    Input *input = nullptr;
    Scene *scene = nullptr;
    Camera2 *camera = nullptr;

    CollisionManager *collisionManager = nullptr;
    CharacterMotor2 characterMotor2;

public:
    Player(Scene &scene, Input &input, CollisionManager &collisionManager, Camera2 &camera);
    void update(float deltaTime);
};