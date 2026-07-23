#pragma once

#include <glm/glm.hpp>

#include "object2.h"
#include "collision_manager.h"
#include "collision_entry.h"

struct Object2;
class CollisionManager;

class CharacterMotor2
{
public:
    void init(Object2 &object, CollisionManager &collisionManager, CollisionEntry &entry);
    MovementResult moveAndSlide(const glm::vec2 &movement);

private:
    Object2 *object = nullptr;
    CollisionManager *collisionManager = nullptr;
    CollisionEntry *collisionEntry = nullptr;
};