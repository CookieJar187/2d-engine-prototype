#include "collision_manager.h"

std::optional<RaycastHit> CollisionManager::raycastAgainstObject(const glm::vec2 &start, const glm::vec2 &end, Object &object)
{
    constexpr float epsilon = 0.000001f;

    if (object.collider == nullptr)
        return std::nullopt;

    const AabbCollider *box = object.collider;
    const glm::vec2 boxCenter = object.transform.position;

    const glm::vec2 localStart = start - boxCenter;
    const glm::vec2 localEnd = end - boxCenter;
    const glm::vec2 direction = localEnd - localStart;

    const float segmentLength = glm::length(direction);

    if (segmentLength <= epsilon)
        return std::nullopt;

    float tMin = 0.0f;
    float tMax = 1.0f;

    glm::vec2 hitNormal(0.0f);

    // X
    if (std::abs(direction.x) > epsilon)
    {
        const float t1 = (-box->halfSize.x - localStart.x) / direction.x;
        const float t2 = (box->halfSize.x - localStart.x) / direction.x;

        const float tNear = std::min(t1, t2);
        const float tFar = std::max(t1, t2);

        const glm::vec2 nearNormal = (t1 < t2) ? glm::vec2(-1.0f, 0.0f) : glm::vec2(1.0f, 0.0f);

        if (tNear > tMin)
        {
            tMin = tNear;
            hitNormal = nearNormal;
        }

        tMax = std::min(tMax, tFar);

        if (tMin > tMax)
            return std::nullopt;
    }
    else
    {
        if (std::abs(localStart.x) > box->halfSize.x)
            return std::nullopt;
    }

    // Y
    if (std::abs(direction.y) > epsilon)
    {
        const float t1 = (-box->halfSize.y - localStart.y) / direction.y;

        const float t2 = (box->halfSize.y - localStart.y) / direction.y;

        const float tNear = std::min(t1, t2);
        const float tFar = std::max(t1, t2);

        const glm::vec2 nearNormal = (t1 < t2) ? glm::vec2(0.0f, -1.0f) : glm::vec2(0.0f, 1.0f);

        if (tNear > tMin)
        {
            tMin = tNear;
            hitNormal = nearNormal;
        }

        tMax = std::min(tMax, tFar);

        if (tMin > tMax)
            return std::nullopt;
    }
    else
    {
        if (std::abs(localStart.y) > box->halfSize.y)
            return std::nullopt;
    }

    RaycastHit hit{};

    hit.object = &object;
    hit.collider = object.collider;
    hit.point = start + (end - start) * tMin;
    hit.normal = hitNormal;
    hit.fraction = tMin;
    hit.distance = segmentLength * tMin;

    return hit;
}

std::optional<RaycastHit> CollisionManager::raycast(
    const glm::vec2 &start,
    const glm::vec2 &end,
    const Object *ignore)
{
    std::optional<RaycastHit> closestHit;
    float closestFraction = 1.0f;

    for (auto &object : world->objects)
    {
        if (object->collider == nullptr)
            continue;

        if (object.get() == ignore)
            continue;

        std::optional<RaycastHit> hit = raycastAgainstObject(start, end, *object.get());

        if (hit.has_value() && hit->fraction < closestFraction)
        {
            closestFraction = hit->fraction;
            closestHit = hit;
        }
    }

    return closestHit;
}