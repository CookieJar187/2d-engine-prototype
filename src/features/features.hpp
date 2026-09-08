#pragma once

#include "core.hpp"

#include "game_assets.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "tilemap.h"
#include "damage_registry.h"
#include "bullet_system.h"
#include "explosion_system.hpp"
#include "grenade_system.hpp"
#include "melee_system.hpp"
#include "character_manager.hpp"
#include "rng.hpp"
#include "camera_shaker.hpp"

class Features
{
private:
    Core *core;

public:
    Features(Core &core) : core(&core)
    {
        tilemap.load();
        characterManager.spawnPlayer({500, -500});
    }

    void update(float deltaTime, float elapsed)
    {
        bulletSystem.update(deltaTime);
        grenadeSystem.update(deltaTime);
        explosionSystem.update(deltaTime);
        meleeSystem.update(deltaTime);
        tilemap.update(deltaTime);
        characterManager.update(deltaTime);
        cameraShaker.update(elapsed);
    }

    GameAssets gameAssets{*core};
    DamageRegistry damageRegistry;
    CameraShaker cameraShaker{*core};
    BulletSystem bulletSystem{*core, damageRegistry};
    ExplosionSystem explosionSystem{*core, damageRegistry, cameraShaker};
    GrenadeSystem grenadeSystem{*core, explosionSystem};
    MeleeSystem meleeSystem{*core, damageRegistry};

    Tilemap tilemap{*core, damageRegistry};

    CharacterManager characterManager{
        *core,
        bulletSystem,
        damageRegistry,
        tilemap,
        grenadeSystem,
        meleeSystem,
        cameraShaker
    };
};