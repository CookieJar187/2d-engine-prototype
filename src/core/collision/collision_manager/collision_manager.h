#pragma once

#include <vector>
#include <optional>
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

struct RaycastHit
{
    Object2 *object = nullptr;
    AabbCollider *collider = nullptr;

    glm::vec2 point = {0.0f, 0.0f};
    glm::vec2 normal = {0.0f, 0.0f};

    float distance = 0.0f;
    float fraction = 0.0f;
};

class CollisionManager
{
private:
    bool isOverlapping(const CollisionEntry &entryA, const CollisionEntry &entryB);

    void resolveHorizontal(CollisionEntry &moving, const CollisionEntry &obstacle, float movementX);
    void resolveVertical(CollisionEntry &moving, const CollisionEntry &obstacle, float movementY);

    std::optional<RaycastHit> raycastAgainstEntry(
        const glm::vec2 &start,
        const glm::vec2 &end,
        const CollisionEntry &entry);

    std::vector<CollisionEntry *> entries;

public:
    MovementResult moveAndSlide(CollisionEntry &moving, const glm::vec2 &movement);

    std::optional<RaycastHit> raycast(
        const glm::vec2 &start,
        const glm::vec2 &end,
        const Object2 *ignore = nullptr
    );

    CollisionEntry *registerObject(Object2 &obj);
    void unregisterObject(Object2 &obj);
};