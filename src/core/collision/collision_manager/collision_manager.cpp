#include <vector>
#include <glm/glm.hpp>

#include "collision_manager.h"

bool CollisionManager::isOverlapping(const CollisionEntry &entryA, const CollisionEntry &entryB)
{
    if (
        entryA.collider == nullptr ||
        entryA.tansform == nullptr ||
        entryB.collider == nullptr ||
        entryB.tansform == nullptr)
    {
        return false;
    }

    const glm::vec2 minA = entryA.tansform->position - entryA.collider->halfSize;
    const glm::vec2 maxA = entryA.tansform->position + entryA.collider->halfSize;

    const glm::vec2 minB = entryB.tansform->position - entryB.collider->halfSize;
    const glm::vec2 maxB = entryB.tansform->position + entryB.collider->halfSize;

    return minA.x < maxB.x &&
           maxA.x > minB.x &&
           minA.y < maxB.y &&
           maxA.y > minB.y;
}

void CollisionManager::resolveHorizontal(CollisionEntry &moving, const CollisionEntry &obstacle, float movementX)
{
    float movingHalfWidth = moving.collider->halfSize.x;
    float obstacleHalfWidth = obstacle.collider->halfSize.x;
    float obstacleCenterX = obstacle.tansform->position.x;

    if (movementX > 0.0f)
        moving.tansform->position.x = obstacleCenterX - obstacleHalfWidth - movingHalfWidth;
    else if (movementX < 0.0f)
        moving.tansform->position.x = obstacleCenterX + obstacleHalfWidth + movingHalfWidth;
}

void CollisionManager::resolveVertical(CollisionEntry &moving, const CollisionEntry &obstacle, float movementY)
{
    float movingHalfHeight = moving.collider->halfSize.y;
    float obstacleHalfHeight = obstacle.collider->halfSize.y;
    float obstacleCenterY = obstacle.tansform->position.y;

    if (movementY > 0.0f)
        moving.tansform->position.y = obstacleCenterY - obstacleHalfHeight - movingHalfHeight;
    else if (movementY < 0.0f)
        moving.tansform->position.y = obstacleCenterY + obstacleHalfHeight + movingHalfHeight;
}

MovementResult CollisionManager::moveAndSlide(CollisionEntry &moving, const glm::vec2 &movement)
{
    MovementResult result;

    const glm::vec2 startingPosition = moving.tansform->position;

    moving.tansform->position.x += movement.x;

    for (CollisionEntry *obstacle : entries)
    {
        if (obstacle == nullptr ||
            obstacle == &moving)
        {
            continue;
        }

        if (!isOverlapping(moving, *obstacle))
            continue;

        resolveHorizontal(moving, *obstacle, movement.x);

        result.collided = true;
    }

    moving.tansform->position.y += movement.y;

    for (CollisionEntry *obstacle : entries)
    {
        if (obstacle == nullptr ||
            obstacle == &moving)
        {
            continue;
        }

        if (!isOverlapping(moving, *obstacle))
            continue;

        resolveVertical(moving, *obstacle, movement.y);

        result.collided = true;
    }

    result.appliedMovement = moving.tansform->position - startingPosition;

    return result;
}