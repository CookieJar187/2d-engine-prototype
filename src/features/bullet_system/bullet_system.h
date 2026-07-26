#pragma once

#include <glm/glm.hpp>
#include "collision_manager.h"
#include "damage_registry.h"

class BulletSystem
{
public:
    BulletSystem(CollisionManager &collisionManager, DamageRegistry &damageRegistry);

    void fire(
        const glm::vec2 &start,
        const glm::vec2 &end,
        const Object2 *ignore = nullptr
    );

private:
    CollisionManager *collisionManager = nullptr;
    DamageRegistry *damageRegistry = nullptr;
};