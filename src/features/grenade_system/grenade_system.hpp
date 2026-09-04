#pragma once

#define GRENADE_SPEED 2.0f
#define GRENADE_TICK_LENGTH 0.07f
#define GRENADE_MIN_TICK_FREQ 0.07f

#include <vector>
#include <glm/vec2.hpp>

#include "object.h"
#include "scene.h"
#include "collision_manager.h"
#include "resource_manager.hpp"

#include "explosion_system.hpp"

struct Grenade
{
    Object *object = nullptr;
    glm::vec2 direction;
    glm::vec2 position;
    float lifespan = 2.2f;
    float momentum = 35.0f;

    float nextTick = 0.4f;
    float tickElapsed = 0.0f;
    int tickState = 1;
};

class GrenadeSystem
{
private:
    std::vector<Grenade> grenades;

    Scene *scene;
    CollisionManager *collisionManager;
    ExplosionSystem *explosionSystem;
    Material *grenadeOn;
    Material *grenadeOff;

    Sound *grenadeBeep;
    RaycastFilter raycastFilter;

    void deleteGrenade(Grenade *grnd, int index);

public:
    GrenadeSystem(
        Scene &scene,
        CollisionManager &collisionManager,
        ResourceManager &resourceManager,
        ExplosionSystem &explosionSystem
    );

    void launch(
        const glm::vec2 origin,
        const glm::vec2 dir
    );

    void update(float deltaTime);
};