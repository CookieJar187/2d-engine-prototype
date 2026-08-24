#pragma once

#define GRENADE_SPEED 2.0f

#include <vector>
#include <glm/vec2.hpp>

#include "object.h"
#include "scene.h"
#include "collision_manager.h"

#include "explosion_system.hpp"

struct Grenade
{
    Object *object = nullptr;
    Object *launcher = nullptr;
    glm::vec2 direction;
    glm::vec2 position;
    float lifespan = 2.0f;
    float momentum = 35.0f;
};

class GrenadeSystem
{
private:
    std::vector<Grenade> grenades;

    Scene *scene;
    CollisionManager *collisionManager;
    ExplosionSystem *explosionSystem;

    void deleteGrenade(Grenade *grnd, int index);

public:
    GrenadeSystem(
        Scene &scene,
        CollisionManager &collisionManager,
        ExplosionSystem &explosionSystem
    );

    void launch(
        const glm::vec2 origin,
        const glm::vec2 dir,
        Object *launcher = nullptr
    );

    void update(float deltaTime);
};