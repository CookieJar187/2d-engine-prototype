#pragma once

#define BULLET_SPEED 3000.0f

#include <vector>
#include <glm/glm.hpp>

#include "scene.h"
#include "collision_manager.h"
#include "damage_registry.h"
#include "resource_manager.hpp"
#include "object.h"

enum class BulletTeam
{
    Friendly,
    Enemy
};

struct Bullet
{
    Object *object = nullptr;
    glm::vec2 direction;
    glm::vec2 position;
    BulletTeam team;
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
        BulletTeam team);

    void update(float deltaTime);

private:
    CollisionManager *collisionManager = nullptr;
    DamageRegistry *damageRegistry = nullptr;
    Scene *scene = nullptr;

    Sound *gunshotSound;
    RaycastFilter friendlyFilter;
    RaycastFilter enemyFilter;

    std::vector<Bullet> bullets;

    void deleteBullet(Bullet *bullet, int index);
};