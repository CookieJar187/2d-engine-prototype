#include "enemy.hpp"

#include <iostream>

#include "rng.hpp"
#include "pathfinding.hpp"

Object *Enemy::getClosestEnemy(Scene &scene)
{
    return scene.getObjectByName("player");
}

void Enemy::updateAi(float deltaTime)
{
    if (isDead() || isBeingDamaged())
        return;

    // Finding the path
    if (lastTimePathfindingWasUpdated < maximumForLastTimePathfindingWasUpdated)
        lastTimePathfindingWasUpdated += deltaTime;
    else
    {
        enemyTarget = getClosestEnemy(*this->scene);

        if (enemyTarget == nullptr)
            return;

        this->navigateTo(enemyTarget->transform.position);

        lastTimePathfindingWasUpdated = 0.0f;
    }

    // Firing at the target
    if (lastTimeGunWasUpdated < maximumForLastTimeGunWasUpdated)
        lastTimeGunWasUpdated += deltaTime;
    else
    {
        if (enemyTarget != nullptr)
        {
            auto originPos = this->body->transform.position;
            auto targetPos = enemyTarget->transform.position;

            std::optional<RaycastHit> result =
                this->collision->raycast(targetPos, originPos, *this->aiVisionRaycastFilter);

            if (!result.has_value())
            {
                glm::vec2 imprecision{rng::getFloat(200.0) - 100, rng::getFloat(200.0) - 100};
                glm::vec2 dir = glm::normalize((targetPos + imprecision) - originPos);
                this->bulletSystem->fire(originPos, dir, BulletTeam::Enemy);
            }

        }
        
        lastTimeGunWasUpdated = rng::getFloat(0.5f);
    }
}