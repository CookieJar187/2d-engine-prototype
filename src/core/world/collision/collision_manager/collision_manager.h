#pragma once

#include <vector>
#include <optional>
#include <glm/glm.hpp>

#include "world.h"
#include "transform2.h"
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

struct RaycastHit
{
    Object *object = nullptr;
    AabbCollider *collider = nullptr;

    glm::vec2 point = {0.0f, 0.0f};
    glm::vec2 normal = {0.0f, 0.0f};

    float distance = 0.0f;
    float fraction = 0.0f;
};

class CollisionManager
{
private:
    bool isOverlapping(const Object &entryA, const Object &entryB);

    void resolveHorizontal(Object &moving, const Object &obstacle, float movementX);
    void resolveVertical(Object &moving, const Object &obstacle, float movementY);

    std::optional<RaycastHit> raycastAgainstObject(
        const glm::vec2 &start,
        const glm::vec2 &end,
        Object &object);

    World *world;

public:
    CollisionManager(World &world);

    MovementResult moveAndSlide(Object &moving, const glm::vec2 &movement);

    std::optional<RaycastHit> raycast(
        const glm::vec2 &start,
        const glm::vec2 &end,
        const Object *ignore = nullptr);
};