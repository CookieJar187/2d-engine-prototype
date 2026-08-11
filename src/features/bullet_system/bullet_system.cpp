#include <iostream>

#include "bullet_system.h"

BulletSystem::BulletSystem(CollisionManager &collisionManager, DamageRegistry &damageRegistry, Scene &scene)
{
    this->collisionManager = &collisionManager;
    this->damageRegistry = &damageRegistry;
    this->scene = &scene;
}

void BulletSystem::fire(
    const glm::vec2 &origin,
    const glm::vec2 &direction,
    Object2 *ignore
)
{
    Transform2 trans{
        .position = origin,
        .rotation = std::atan2(direction.y, direction.x)
    };

    ObjectCreationResult bulletObject = this->scene->createObject(
        {.name = "bullet", .materialName = "bullet", .transform = trans});

    Bullet bullet = {
        .object = bulletObject.object,
        .ignore = ignore,
        .direction = direction,
        .position = origin,
        .index = bullets.size()
    };

    bullets.push_back(bullet);
}

void BulletSystem::update(float deltaTime)
{
    for (auto &bullet : bullets)
    {
        glm::vec2 targetPos = bullet.position + (bullet.direction * BULLET_SPEED * deltaTime);
        
        std::optional<RaycastHit> hit = BulletSystem::collisionManager->raycast(
            bullet.position,
            targetPos,
            bullet.ignore);

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
            deleteBullet(bullet);
        }
        else
        {
            bullet.object->transform.position = targetPos;
            bullet.position = targetPos;
            bullet.lifespan -= deltaTime;

            if (bullet.lifespan < 0)
                deleteBullet(bullet);
        }
    }
}

void BulletSystem::deleteBullet(Bullet &bullet)
{
    int index = bullet.index;

    bullets.erase(bullets.begin() + index);
}