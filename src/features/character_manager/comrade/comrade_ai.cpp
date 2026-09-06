#include "comrade.hpp"

#include <iostream>

#include "rng.hpp"
#include "pathfinding.hpp"

Object *Comrade::getClosestEnemy(Scene &scene)
{
    return scene.getObjectByName("player");
}

void Comrade::updateAi(float deltaTime)
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
        /*
        if (enemyTarget != nullptr)
        {
            auto originPos = this->body->transform.position;
            auto targetPos = enemyTarget->transform.position;

            std::optional<RaycastHit> result =
                this->collisionManager->raycast(targetPos, originPos, this->body);

            if (result.has_value())
            {
                //std::cout << "visible\n";
                
                glm::vec2 imprecision{rng::getFloat(200.0) - 100, rng::getFloat(200.0) - 100};
                glm::vec2 dir = glm::normalize((targetPos + imprecision) - originPos);
                this->bulletSystem->fire(originPos, dir, this->body);
            }
        }
        */
        lastTimeGunWasUpdated = rng::getFloat(0.5f);
    }
}