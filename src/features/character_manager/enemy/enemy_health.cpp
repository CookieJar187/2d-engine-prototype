#include "enemy.h"

#include <iostream>

void Enemy::updateHealth(float deltaTime)
{
    if (this->dead)
    {
        this->deathEffectElapsed += deltaTime;

        if (this->deathEffectElapsed > DEATH_EFFECT_DURATION)
        {
            queueFree();
        }
    }
    else if (this->damageEffect == true)
    {
        this->damageEffectElapsed += deltaTime;

        if (this->damageEffectElapsed > DAMAGE_EFFECT_DURATION)
        {
            this->damageEffect = false;
            this->body->material->texture = this->resourceManager->getTexture("enemy_texture");
        }
    }
}

void Enemy::death()
{
    this->dead = true;
}

void Enemy::takeDamage(int amount)
{
    if (this->dead)
        return;

    this->body->material->texture = this->resourceManager->getTexture("enemy_hit_texture");

    health -= amount;
    if (health <= 0.0f)
        return death();

    this->damageEffectElapsed = 0.0f;
    this->damageEffect = true;
}