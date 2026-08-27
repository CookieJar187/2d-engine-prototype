#include "destructable_wall.hpp"

#include <iostream>

DestructableWall::DestructableWall(
    Scene &scene,
    DamageRegistry &damageRegistry,
    ObjectCreationData creationData,
    short int maxHealthPoints,
    Material &defaultMaterial,
    Material &hitMaterial,
    Material &damagedMaterial,
    Material &destroyedMaterial
)
: Wall(scene, creationData)
{
    this->damageRegistry = &damageRegistry;

    this->maxHealthPoints = maxHealthPoints;
    this->healthPoints = maxHealthPoints;
    
    this->defaultMaterial = &defaultMaterial;
    this->hitMaterial = &hitMaterial;
    this->damagedMaterial = &damagedMaterial;
    this->destroyedMaterial = &destroyedMaterial;

    damageRegistry.registerDamageable(this->obj, this);
}

DestructableWall::~DestructableWall()
{
    this->damageRegistry->unregisterDamageable(this->obj);
}

void DestructableWall::update(float deltaTime)
{
    if (this->destroyed)
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

            if (healthPoints < this->maxHealthPoints * 0.5f)
                this->obj->material = this->damagedMaterial;
            else
                this->obj->material = this->defaultMaterial;
        }
    }
}

void DestructableWall::takeDamage(int amount)
{
    if (this->destroyed)
        return;

    healthPoints -= amount;
    if (healthPoints <= 0.0f)
    {
        this->destroyed = true;
        this->obj->material = this->destroyedMaterial;
        this->obj->collider = nullptr;
        return;
    }

    this->damageEffectElapsed = 0.0f;
    this->damageEffect = true;
    this->obj->material = hitMaterial;
}