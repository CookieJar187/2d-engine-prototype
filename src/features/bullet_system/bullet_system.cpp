#include "bullet_system.h"

BulletSystem::BulletSystem(CollisionManager &collisionManager)
{
    BulletSystem::collisionManager = &collisionManager;
}

void BulletSystem::fire(const glm::vec2 &start, const glm::vec2 &end)
{
    BulletSystem::collisionManager->raycast(start, end);
}