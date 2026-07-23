#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "transform2.h"
#include "object2.h"
#include "collision_entry.h"

struct CollisionResult
{
    bool collided = false;
    glm::vec2 normal{0.0f};
    float penetration = 0.0f;
    Object2 *obstacle = nullptr;
};

struct MovementResult
{
    glm::vec2 requestedMovement{0.0f};
    glm::vec2 appliedMovement{0.0f};

    bool collided = false;

    std::vector<CollisionResult> collisions;
};

class CollisionManager
{
private:
    bool isOverlapping(const CollisionEntry &entryA, const CollisionEntry &entryB);

    void resolveHorizontal(CollisionEntry &moving, const CollisionEntry &obstacle, float movementX);
    void resolveVertical(CollisionEntry &moving, const CollisionEntry &obstacle, float movementY);

    std::vector<CollisionEntry *> entries;

public:
    MovementResult moveAndSlide(CollisionEntry &moving, const glm::vec2 &movement);

    CollisionEntry *registerObject(Object2 &obj);
    void unregisterObject(Object2 &obj);
};