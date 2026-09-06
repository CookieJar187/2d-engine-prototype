#pragma once

#include <vector>
#include <glm/vec2.hpp>

#include "core.hpp"
#include "damage_registry.h"
#include "camera_shaker.hpp"

struct Explosion
{
    Object *object;
    glm::vec2 pos;
    float radius = 200.0f;
    float lifespan = 0.07f;
};

class ExplosionSystem
{
private:
    std::vector<Explosion> explosions;

    Scene *scene;
    DamageRegistry *damageRegistry;
    CameraShaker *cameraShaker;

    Sound *explosion1Sound;
    Sound *explosion2Sound;
    Sound *explosion3Sound;

    void deleteExplosion(Explosion *expl, int index);

public:
    ExplosionSystem(
        Core &core,
        DamageRegistry &damageRegistry,
        CameraShaker &cameraShaker
    );

    void explode(const glm::vec2 pos);

    void update(float deltaTime);

};