#pragma once

#include <vector>
#include <glm/vec2.hpp>

#include "scene.h"
#include "damage_registry.h"

struct Melee
{
    Object *object;
    Object *parentObject;
    //glm::vec2 pos;
    float radius = 120.0f;
    float lifespan = 0.07f;
};

class MeleeSystem
{
private:
    std::vector<Melee> melees;

    Scene *scene;
    DamageRegistry *damageRegistry;

    void deleteMelee(Melee *expl, int index);

public:
    MeleeSystem(Scene &scene, DamageRegistry &damageRegistry);

    void newMelee(const glm::vec2 pos, Object &parentObject);

    void update(float deltaTime);

};