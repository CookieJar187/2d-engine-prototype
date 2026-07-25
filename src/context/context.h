#pragma once

#include "game_fsm.h"
#include "asset_library.h"
#include "ui_manager.h"
#include "collision_manager.h"
#include "camera2.h"
#include "scene.h"
#include "input.h"
#include "damage_registry.h"
#include "bullet_system.h"

struct Context
{
    GameFsm *gameFsm = nullptr;
    AssetLibrary *assetLibrary = nullptr;
    UiManager *uiManager = nullptr;
    CollisionManager *collisionManager = nullptr;
    Camera2 *camera2 = nullptr;
    Scene *scene = nullptr;
    Input *input = nullptr;
    DamageRegistry *damageRegistry = nullptr;
    BulletSystem *bulletSystem = nullptr;
};