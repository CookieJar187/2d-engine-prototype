#include "character.hpp"

#include <iostream>

#include "rng.hpp"

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
            this->body->material = downMaterial;
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
        
        if (rng::getInt(2) == 1)
            this->body->material = dead1Material;
        else
            this->body->material = dead2Material;

        this->body->collider = nullptr;

        int randNum = rng::getInt(4);
        if (randNum == 0)
            this->death1Sound->play();
        else if (randNum == 1)
            this->death2Sound->play();
        else if (randNum == 2)
            this->death3Sound->play();
        else if (randNum == 3)
            this->death4Sound->play();

        onKilled();
        return;
    }

    this->damageEffectElapsed = 0.0f;
    this->damageEffect = true;
    this->body->material = hitMaterial;
}