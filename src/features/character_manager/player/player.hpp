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
#include "melee_system.hpp"
#include "camera_shaker.hpp"

class Player : public Character
{
private:
    Camera2 *camera;
    Input *input;
    BulletSystem *bulletSystem;
    GrenadeSystem *grenadeSystem;
    MeleeSystem *meleeSystem;
    CameraShaker *cameraShaker;

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
        MeleeSystem &meleeSystem,
        CameraShaker &cameraShaker,
        glm::vec2 position
    );

    ~Player();

    void update(float deltaTime);
};