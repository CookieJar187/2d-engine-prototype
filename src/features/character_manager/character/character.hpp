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
    std::vector<glm::ivec2> pathPoints;
    int currPathPoint = 0;

    glm::vec2 velocity{0, -1};

    // Pointers to services
    Tilemap *tilemap;
    DamageRegistry *damageRegistry;

    // Materials
    Material *upMaterial;
    Material *downMaterial;
    Material *rightMaterial;
    Material *leftMaterial;
    Material *hitMaterial;
    Material *dead1Material;
    Material *dead2Material;

    Sound *death1Sound;
    Sound *death2Sound;
    Sound *death3Sound;
    Sound *death4Sound;

public:
    Object *body = nullptr;
    CharacterMotor characterMotor;

    Character(   
        Scene &scene,
        CollisionManager &collisionManager,
        DamageRegistry &damageRegistry,
        Tilemap &tilemap,
        ObjectCreationData objectCreationData,
        Material &upMaterial,
        Material &downMaterial,
        Material &rightMaterial,
        Material &leftMaterial,
        Material &hitMaterial,
        Material &dead1Material,
        Material &dead2Material,
        Sound &death1Sound,
        Sound &death2Sound,
        Sound &death3Sound,
        Sound &death4Sound
    );

    virtual ~Character();

    void updateHealth(float deltaTime);
    void updateMovement(float deltaTime);
    void updateAnimation(float deltaTime);

    // Check
    bool isDead() const;
    bool isBeingDamaged() const;

    // Deletion
    bool queuedForDeletion = false;
    void queueFree();
    
    // Control
    void takeDamage(int amount) override;
    void moveTo(glm::vec2 targetPos, float deltaTime);
    void navigateTo(glm::vec2 position);

    // Events
    virtual void onDamageApplied();
    virtual void onDamageStopped();
    virtual void onKilled();
};