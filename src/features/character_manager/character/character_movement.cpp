#include "character.hpp"

#include "pathfinding.hpp"

#include <iostream>

void Character::moveTo(glm::vec2 direction, float deltaTime)
{
    velocity = glm::normalize(direction);
    velocity.x *= MAX_SPEED * deltaTime;
    velocity.y *= MAX_SPEED * deltaTime;

    //characterMotor.moveAndSlide(velocity);
    collision->moveAndSlide(*this->body, velocity);
}

void Character::navigateTo(glm::vec2 targetPos)
{
    glm::vec2 originPos = body->transform.position;

    pathPoints = pathfinding::getPathTo(
        tilemap->worldToTile(originPos),
        tilemap->worldToTile(targetPos),
        *tilemap
    );

    currPathPoint = 0;
}

void Character::updateMovement(float deltaTime)
{
    if (isDead() || isBeingDamaged())
        return;

    if (pathPoints.size() == 0 || currPathPoint >= pathPoints.size())
        return;

    glm::vec2 originPos = body->transform.position;
    glm::vec2 targetPos = tilemap->tileToWorld(pathPoints[currPathPoint]);

    if (glm::distance(originPos, targetPos) > 1.0f)
    {
        velocity = glm::normalize(targetPos - originPos);
        velocity.x *= MAX_SPEED * deltaTime;
        velocity.y *= MAX_SPEED * deltaTime;

        //characterMotor.moveAndSlide(velocity);
        collision->moveAndSlide(*this->body, velocity);
    }
    else
        currPathPoint++;
}