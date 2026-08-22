#pragma once

#define MAX_SPEED 200

#include <memory>

#include "input.h"
#include "camera.h"
#include "scene.h"

#include "character.hpp"
#include "bullet_system.h"
#include "damage_registry.h"
#include "tilemap.h"

class Player : public Character
{
private:
    Camera2 *camera  = nullptr;
    Input *input = nullptr;
    BulletSystem *bulletSystem = nullptr;

public:
    Player(
        Scene &scene,
        Input &input,
        Camera2 &camera,
        CollisionManager &collisionManager,
        BulletSystem &bulletSystem,
        DamageRegistry &damageRegistry,
        Tilemap &tilemap
    );

    ~Player();

    void update(float deltaTime);
};