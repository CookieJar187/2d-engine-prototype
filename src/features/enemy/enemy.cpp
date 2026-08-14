#include "enemy.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>

Enemy::Enemy(
    Scene &scene,
    DamageRegistry &damageRegistry,
    CollisionManager &collisionManager
)
{
    Enemy::scene = &scene;
    Enemy::damageRegistry = &damageRegistry;

    Enemy::body = Enemy::scene->createObject(
        {.name = "enemy",
         .colliderName = "enemy",
         .materialName = "enemy"});

    CharacterMotor.init(*Enemy::body, collisionManager);

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