#include <vector>
#include <glm/glm.hpp>

#include "collision_manager.h"

CollisionManager::CollisionManager(World &world)
{
    this->world = &world;
}

bool CollisionManager::isOverlapping(const Object &obj1, const Object &obj2)
{
    if (
        obj1.collider == nullptr ||
        obj2.collider == nullptr)
    {
        return false;
    }

    const glm::vec2 minA = obj1.transform.position - obj1.collider->halfSize;
    const glm::vec2 maxA = obj1.transform.position + obj1.collider->halfSize;

    const glm::vec2 minB = obj2.transform.position - obj2.collider->halfSize;
    const glm::vec2 maxB = obj2.transform.position + obj2.collider->halfSize;

    return minA.x < maxB.x &&
           maxA.x > minB.x &&
           minA.y < maxB.y &&
           maxA.y > minB.y;
}

void CollisionManager::resolveHorizontal(Object &moving, const Object &obstacle, float movementX)
{
    float movingHalfWidth = moving.collider->halfSize.x;
    float obstacleHalfWidth = obstacle.collider->halfSize.x;
    float obstacleCenterX = obstacle.transform.position.x;

    if (movementX > 0.0f)
        moving.transform.position.x = obstacleCenterX - obstacleHalfWidth - movingHalfWidth;
    else if (movementX < 0.0f)
        moving.transform.position.x = obstacleCenterX + obstacleHalfWidth + movingHalfWidth;
}

void CollisionManager::resolveVertical(Object &moving, const Object &obstacle, float movementY)
{
    float movingHalfHeight = moving.collider->halfSize.y;
    float obstacleHalfHeight = obstacle.collider->halfSize.y;
    float obstacleCenterY = obstacle.transform.position.y;

    if (movementY > 0.0f)
        moving.transform.position.y = obstacleCenterY - obstacleHalfHeight - movingHalfHeight;
    else if (movementY < 0.0f)
        moving.transform.position.y = obstacleCenterY + obstacleHalfHeight + movingHalfHeight;
}

MovementResult CollisionManager::moveAndSlide(Object &moving, const glm::vec2 &movement)
{
    MovementResult result;

    const glm::vec2 startingPosition = moving.transform.position;

    moving.transform.position.x += movement.x;

    for (auto &obstacle : world->objects)
    {
        if (obstacle == nullptr ||
            obstacle.get() == &moving)
        {
            continue;
        }

        if (!isOverlapping(moving, *obstacle))
            continue;

        resolveHorizontal(moving, *obstacle, movement.x);

        result.collided = true;
    }

    moving.transform.position.y += movement.y;

    for (auto &obstacle : world->objects)
    {
        if (obstacle == nullptr ||
            obstacle.get() == &moving)
        {
            continue;
        }

        if (!isOverlapping(moving, *obstacle))
            continue;

        resolveVertical(moving, *obstacle, movement.y);

        result.collided = true;
    }

    result.appliedMovement = moving.transform.position - startingPosition;

    return result;
}