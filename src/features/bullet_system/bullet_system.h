#pragma once

#define BULLET_SPEED 3000.0f

#include <vector>
#include <glm/glm.hpp>

#include "scene.h"
#include "collision_manager.h"
#include "damage_registry.h"
#include "resource_manager.hpp"
#include "object.h"

struct Bullet
{
    Object *object = nullptr;
    Object *ignore = nullptr;
    glm::vec2 direction;
    glm::vec2 position;
    float lifespan = 0.3f;
};

class BulletSystem
{
public:
    BulletSystem(
        CollisionManager &collisionManager,
        DamageRegistry &damageRegistry,
        Scene &scene,
        ResourceManager &resourceManager
    );

    void fire(
        const glm::vec2 &origin,
        const glm::vec2 &direction,
        Object *ignore = nullptr);

    void update(float deltaTime);

private:
    CollisionManager *collisionManager = nullptr;
    DamageRegistry *damageRegistry = nullptr;
    Scene *scene = nullptr;

    Sound *gunshotSound;

    std::vector<Bullet> bullets;

    void deleteBullet(Bullet *bullet, int index);
};