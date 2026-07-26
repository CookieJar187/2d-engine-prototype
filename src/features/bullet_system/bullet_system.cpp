#include <iostream>
#include "bullet_system.h"

BulletSystem::BulletSystem(CollisionManager &collisionManager, DamageRegistry &damageRegistry)
{
    this->collisionManager = &collisionManager;
    this->damageRegistry = &damageRegistry;
}

void BulletSystem::fire(
    const glm::vec2 &start,
    const glm::vec2 &end,
    const Object2 *ignore
)
{
    std::optional<RaycastHit> hit = BulletSystem::collisionManager->raycast(start, end, ignore);

    if (hit.has_value())
    {
        Damageable *damageable = damageRegistry->getDamageable(hit->object);

        if (damageable != nullptr)
        {
            damageable->takeDamage(25.0f);
        }
        else
        {
            std::cout << "Hit a wall!" << std::endl;
        }
    }
    else
        std::cout << "nothing hit" << std::endl;
}