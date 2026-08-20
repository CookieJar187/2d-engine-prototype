#include "enemy.h"

#include "pathfinding.hpp"

void Enemy::navigateTo(glm::ivec2 pos)
{
    if (targetPos == pos)
        return;

    targetPos = pos;

    pathToTarget = pathfinding::getPathTo(
        this->body->transform.position,
        pos,
        *this->tileset
    );

    pathPointsReached = 0;
}

void Enemy::updateMove(float deltaTime)
{
    if (pathPointsReached >= pathToTarget.size())
        return;

    glm::vec2 origin = this->body->transform.position;
    glm::vec2 target = pathToTarget[pathPointsReached];

    if ((target - origin).length() < 10)
    {
        pathPointsReached++;
        return;
    }

    glm::vec2 dir = glm::normalize(target - origin);
    this->CharacterMotor.moveAndSlide(dir);
}