#pragma once

#define MAX_SPEED 200
#define DAMAGE_EFFECT_DURATION 0.07f
#define DEATH_EFFECT_DURATION 5.0f

#include <vector>
#include <glm/vec2.hpp>

#include "object.h"
#include "scene.h"
#include "character_motor.h"
#include "collision_manager.h"

#include "damageable.h"
#include "damage_registry.h"
#include "tilemap.h"

class Character : public Damageable
{
private:
    // Health
    int healthPoints = 100;
    bool dead = false;

    float damageEffectElapsed = 0.0f;
    float deathEffectElapsed = 0.0f;
    bool damageEffect = false;

    // Movement
    glm::ivec2 targetPos;
    std::vector<glm::ivec2> pathToTarget;

    int pathPointsReached = 0;

    // Pointers to services
    Tilemap *tilemap;

public:
    Object *body = nullptr;
    CharacterMotor characterMotor;

    Character(   
        Scene &scene,
        CollisionManager &collisionManager,
        DamageRegistry &damageRegistry,
        Tilemap &tilemap,
        ObjectCreationData objectCreationData
    );

    virtual ~Character();

    //void update(float deltaTime);
    void updateHealth(float deltaTime);
    void updateMovement(float deltaTime);

    // Deletion
    bool queuedForDeletion = false;
    void queueFree();
    
    // Control
    void takeDamage(int amount) override;
    void navigateTo(glm::ivec2 pos);

    // Events
    virtual void onDamageApplied();
    virtual void onDamageStopped();
    virtual void onKilled();
};