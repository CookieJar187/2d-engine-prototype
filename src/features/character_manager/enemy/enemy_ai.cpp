#include "enemy.hpp"

#include <iostream>

#include "pathfinding.hpp"

Object *getClosestEnemy(Scene &scene)
{
    return scene.getObjectByName("player");
}

void Enemy::updateAi(float deltaTime)
{
    if (isDead() || isBeingDamaged())
        return;

    // Finding the path
    if (lastTimePathfindingWasUpdated < maximumForLastTimePathfindingWasUpdated)
    {
        lastTimePathfindingWasUpdated += deltaTime;
    }
    else
    {
        Object *enemy = getClosestEnemy(*this->scene);

        if (enemy == nullptr)
            return;

        glm::vec2 originPos = body->transform.position;
        glm::vec2 targetPos = enemy->transform.position;

        pathPoints = pathfinding::getPathTo(
            tileset->worldToTile(originPos),
            tileset->worldToTile(targetPos),
            *tileset
        );

        currPathPoint = 0;
        lastTimePathfindingWasUpdated = 0;
    }

    // Following the path
    if (pathPoints.size() == 0 || currPathPoint >= pathPoints.size())
        return;

    glm::vec2 originPos = body->transform.position;
    glm::vec2 targetPos = tileset->tileToWorld(pathPoints[currPathPoint]);

    if (glm::distance(originPos, targetPos) > 1.0f)
    {
        glm::vec2 velocity = glm::normalize(targetPos - originPos);
        velocity.x *= MAX_SPEED * deltaTime;
        velocity.y *= MAX_SPEED * deltaTime;

        characterMotor.moveAndSlide(velocity);
    }
    else
        currPathPoint++;
}