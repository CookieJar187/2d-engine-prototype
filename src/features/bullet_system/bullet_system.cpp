#include <iostream>

#include "bullet_system.h"

BulletSystem::BulletSystem(
    Core &core,
    DamageRegistry &damageRegistry
)
{
    this->collision = &core.collision;
    this->damageRegistry = &damageRegistry;
    this->scene = &core.scene;

    this->gunshotSound = core.resourceManager.getSound("gunshot1_sound");
    CollisionGroup *friendlyCollisionGroup = core.resourceManager.getCollisionGroup("friendly_character_collision_group");
    CollisionGroup *enemyCollisionGroup = core.resourceManager.getCollisionGroup("enemy_character_collision_group");

    this->friendlyFilter.groups = (1u << friendlyCollisionGroup->id);
    this->enemyFilter.groups = (1u << enemyCollisionGroup->id);
}

void BulletSystem::fire(
    const glm::vec2 &origin,
    const glm::vec2 &direction,
    BulletTeam team)
{
    Transform2 trans{
        .position = origin,
        .rotation = std::atan2(direction.y, direction.x),
        .scale = glm::vec2(50, 50)};

    Object *bulletObject = this->scene->createObject({
        .name = "bullet",
        .meshId = "sprite_mesh",
        .materialId = "bullet_material",
        .transform = trans});

    Bullet bullet = {
        .object = bulletObject,
        .direction = direction,
        .position = origin,
        .team = team};

    bullets.push_back(bullet);

    this->gunshotSound->play();
}

void BulletSystem::update(float deltaTime)
{
    for (int i = bullets.size() - 1; i >= 0; i--)
    {
        Bullet *bullet = &bullets[i];

        glm::vec2 targetPos = bullet->position + (bullet->direction * BULLET_SPEED * deltaTime);

        RaycastFilter *raycastFilter = nullptr;
        if (bullet->team == BulletTeam::Friendly)
            raycastFilter = &this->friendlyFilter;
        else
            raycastFilter = &this->enemyFilter;

        std::optional<RaycastHit> hit = BulletSystem::collision->raycast(
            bullet->position,
            targetPos,
            *raycastFilter
        );

        if (hit.has_value())
        {
            Damageable *damageable = damageRegistry->getDamageable(hit->object);
            
            if (damageable != nullptr)
            {
                damageable->takeDamage(34);
            }
            else
            {
                //std::cout << "Hit a wall!" << std::endl;
            }
            deleteBullet(bullet, i);
        }
        else
        {
            bullet->object->transform.position = targetPos;
            bullet->position = targetPos;
            bullet->lifespan -= deltaTime;

            if (bullet->lifespan < 0)
                deleteBullet(bullet, i);
        }
    }
}

void BulletSystem::deleteBullet(Bullet *bullet, int index)
{
    bullet->object->queueFree();
    bullets.erase(bullets.begin() + index);
}