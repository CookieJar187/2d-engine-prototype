#pragma once

#include <glm/glm.hpp>
#include "collision_manager.h"

class BulletSystem
{
public:
    BulletSystem(CollisionManager &collisionManager);

    void fire(const glm::vec2 &start, const glm::vec2 &end);

private:
    CollisionManager *collisionManager = nullptr;
};