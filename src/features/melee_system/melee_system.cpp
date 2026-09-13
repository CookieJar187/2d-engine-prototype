#include "melee_system.hpp"

#include <iostream>

MeleeSystem::MeleeSystem(
    Core &core,
    DamageRegistry &damageRegistry
)
{
    this->scene = &core.scene;
    this->damageRegistry = &damageRegistry;
}

void MeleeSystem::newMelee(Object &parentObject)
{
    ObjectCreationData d;
    d.name = "melee";
    d.meshId = "sprite_mesh";
    d.materialId = "melee_material";
    d.transform = { .scale = glm::vec2{1, 1} };
    d.parent = &parentObject;

    Melee melee;
    melee.object = this->scene->createObject(d);

    this->melees.push_back(melee);

    std::unordered_map<Object *, Damageable *> damageables
        = this->damageRegistry->getDamageables();
    
    for (auto &entry : damageables)
    {
        if (glm::distance(parentObject.transform.position, entry.first->transform.position) <= melee.radius
        && entry.first != &parentObject)
        {
            entry.second->takeDamage(75);
        }
    }
}

void MeleeSystem::update(float deltaTime)
{
    for (int i = melees.size() - 1; i >= 0; i--)
    {
        Melee *melee = &melees[i];

        if (melee->lifespan <= 0)
            deleteMelee(melee, i);
        else
        {
            melee->object->transform.rotation -= 70 * deltaTime;
            melee->lifespan -= deltaTime;
        }
    }
}

void MeleeSystem::deleteMelee(Melee *melee, int index)
{
    melee->object->queueFree();
    melees.erase(melees.begin() + index);
}