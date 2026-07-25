#include "enemy.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>

Enemy::Enemy(Context &ctx)
{
    Enemy::scene = ctx.scene;
    Enemy::damageRegistry = ctx.damageRegistry;

    ObjectCreationResult result = Enemy::scene->createObject(
        {.name = "enemy",
         .colliderName = "enemy",
         .materialName = "enemy"});

    Enemy::body = result.object;
    characterMotor2.init(*Enemy::body, *ctx.collisionManager, *result.collisionEntry);

    Enemy::damageRegistry->registerDamageable(Enemy::body, this);
}

void Enemy::update(float deltaTime)
{
    if (body == nullptr)
        return;
}

void Enemy::die()
{
    std::cout << "Enemy died" << std::endl;
}

void Enemy::takeDamage(float amount)
{
    health -= amount;
    std::cout << "Enemy has taken damage" << std::endl;

    if (health <= 0.0f)
    {
        die();
    }
}