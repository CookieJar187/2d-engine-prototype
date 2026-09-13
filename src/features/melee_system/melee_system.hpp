#pragma once

#include <vector>
#include <glm/vec2.hpp>

#include "core.hpp"
#include "damage_registry.h"

struct Melee
{
    Object *object;
    float radius = 120.0f;
    float lifespan = 0.07f;
};

class MeleeSystem
{
private:
    std::vector<Melee> melees;

    Scene *scene;
    DamageRegistry *damageRegistry;

    void deleteMelee(Melee *melee, int index);

public:
    MeleeSystem(Core &core, DamageRegistry &damageRegistry);

    void newMelee(Object &parentObject);

    void update(float deltaTime);

};