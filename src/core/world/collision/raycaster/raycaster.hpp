#pragma once

#include <vector>
#include <optional>
#include <glm/vec2.hpp>

#include "world.h"
#include "object.h"

enum class GroupFilterMode
{
    Ignore,
    PermitOnly
};

struct RaycastFilter
{
    CollisionMask groups = 0;
    GroupFilterMode mode = GroupFilterMode::Ignore;
};

struct RaycastHit
{
    Object *object = nullptr;
    Collider *collider = nullptr;

    glm::vec2 point = {0.0f, 0.0f};
    glm::vec2 normal = {0.0f, 0.0f};

    float distance = 0.0f;
    float fraction = 0.0f;
};

class Raycaster{
private:
    World *world;

    std::optional<RaycastHit> raycastAgainstObject(
        const glm::vec2 &start, 
        const glm::vec2 &end,
        Object &object
    );

public:
    Raycaster(World &world);

    std::optional<RaycastHit> raycast(
        const glm::vec2 &start,
        const glm::vec2 &end,
        const RaycastFilter filter
    );
};