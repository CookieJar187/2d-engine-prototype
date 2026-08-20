#include "character.hpp"

#include <iostream>

void Character::updateHealth(float deltaTime)
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
            onDamageStopped();
        }
    }
}

void Character::takeDamage(int amount)
{
    if (this->dead)
        return;

    onDamageApplied();

    healthPoints -= amount;
    if (healthPoints <= 0.0f)
    {
        this->dead = true;
        onKilled();
        return;
    }

    this->damageEffectElapsed = 0.0f;
    this->damageEffect = true;
}