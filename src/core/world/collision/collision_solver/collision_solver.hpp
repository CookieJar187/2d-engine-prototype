#pragma once

#include <vector>
#include <glm/vec2.hpp>

#include "world.hpp"
#include "object.h"

struct CollisionResult
{
    bool collided = false;
    glm::vec2 normal{0.0f};
    float penetration = 0.0f;
    Object *obstacle = nullptr;
};

struct MovementResult
{
    glm::vec2 requestedMovement{0.0f};
    glm::vec2 appliedMovement{0.0f};

    bool collided = false;

    std::vector<CollisionResult> collisions;
};

class CollisionSolver
{
private:
    World *world;

    bool canCollide(const CollisionGroup& a, const CollisionGroup& b) const;
    bool isOverlapping(const Object &obj1, const Object &obj2) const;

    void resolveHorizontal(Object &moving, const Object &obstacle, float movementX);
    void resolveVertical(Object &moving, const Object &obstacle, float movementY);

public:
    CollisionSolver(World &world);

    MovementResult moveAndSlide(Object &moving, const glm::vec2 &movement);
};