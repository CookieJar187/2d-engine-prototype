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

        this->navigateTo(enemy->transform.position);

        lastTimePathfindingWasUpdated = 0.0f;
    }
}