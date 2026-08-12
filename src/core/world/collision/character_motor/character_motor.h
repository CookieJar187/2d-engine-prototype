#pragma once

#include <glm/glm.hpp>

#include "object.h"
#include "collision_manager.h"

struct Object;
class CollisionManager;

class CharacterMotor
{
public:
    void init(Object &object, CollisionManager &collisionManager);
    MovementResult moveAndSlide(const glm::vec2 &movement);

private:
    Object *object = nullptr;
    CollisionManager *collisionManager = nullptr;
};