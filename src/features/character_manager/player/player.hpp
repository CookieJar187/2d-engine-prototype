#pragma once

#define MAX_SPEED 200

#include <memory>

#include "input.h"
#include "camera.h"
#include "scene.h"
#include "resource_manager.hpp"

#include "character.hpp"
#include "bullet_system.h"
#include "damage_registry.h"
#include "tilemap.h"
#include "grenade_system.hpp"

class Player : public Character
{
private:
    Camera2 *camera  = nullptr;
    Input *input = nullptr;
    BulletSystem *bulletSystem = nullptr;
    GrenadeSystem *grenadeSystem = nullptr;

public:
    Player(
        Scene &scene,
        Input &input,
        Camera2 &camera,
        CollisionManager &collisionManager,
        ResourceManager &resourceManager,
        BulletSystem &bulletSystem,
        DamageRegistry &damageRegistry,
        Tilemap &tilemap,
        GrenadeSystem &grenadeSystem,
        glm::vec2 position
    );

    ~Player();

    void update(float deltaTime);
};