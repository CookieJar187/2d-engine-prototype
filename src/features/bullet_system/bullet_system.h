#pragma once

#define BULLET_SPEED 1500.0f

#include <vector>
#include <glm/glm.hpp>

#include "scene.h"
#include "collision_manager.h"
#include "damage_registry.h"
#include "object.h"

struct Bullet
{
    Object *object = nullptr;
    Object *ignore = nullptr;
    glm::vec2 direction;
    glm::vec2 position;
    float lifespan = 0.5f;
    unsigned __int64 index;
};

class BulletSystem
{
public:
    BulletSystem(CollisionManager &collisionManager, DamageRegistry &damageRegistry, Scene &scene);

    void fire(
        const glm::vec2 &origin,
        const glm::vec2 &direction,
        Object *ignore = nullptr);

    void update(float deltaTime);

private:
    CollisionManager *collisionManager = nullptr;
    DamageRegistry *damageRegistry = nullptr;
    Scene *scene = nullptr;

    std::vector<Bullet> bullets;

    void deleteBullet(Bullet &bullet);
};