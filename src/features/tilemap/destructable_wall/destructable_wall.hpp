#pragma once

#define DAMAGE_EFFECT_DURATION 0.07f
#define DEATH_EFFECT_DURATION 5.0f

#include "wall.hpp"
#include "damage_registry.h"

struct DestructableWall : public Wall, public Damageable
{
private:
    short int maxHealthPoints;
    short int healthPoints;
    bool destroyed = false;

    float damageEffectElapsed = 0.0f;
    float deathEffectElapsed = 0.0f;
    bool damageEffect = false;
    
    Material *defaultMaterial;
    Material *hitMaterial;
    Material *damagedMaterial;
    Material *destroyedMaterial;

public:
    DestructableWall(
        Scene &scene,
        DamageRegistry &damageRegistry,
        ObjectCreationData creationData,
        short int maxHealthPoints,
        Material &defaultMaterial,
        Material &hitMaterial,
        Material &damagedMaterial,
        Material &destroyedMaterial
    );
    ~DestructableWall();

    void update(float deltaTime);

    void takeDamage(int amount) override;

    DamageRegistry *damageRegistry;
};