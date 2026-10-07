#pragma once

#define MAX_SPEED 200

#include <memory>

#include "core.hpp"

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
        Core &core,
        DamageRegistry &damageRegistry,
        BulletSystem &bulletSystem,
        Tilemap &tilemap,
        GrenadeSystem &grenadeSystem,
        MeleeSystem &meleeSystem,
        CameraShaker &cameraShaker,
        glm::vec2 position
    );

    ~Player();

    void update(float deltaTime);
};