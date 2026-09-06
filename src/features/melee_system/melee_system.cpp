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

void MeleeSystem::newMelee(const glm::vec2 pos, Object &parentObject)
{
    ObjectCreationData d;
    d.name = "melee";
    d.meshId = "sprite_mesh";
    d.materialId = "melee_material";
    d.transform = { .position = pos };

    Melee melee;
    melee.object = this->scene->createObject(d);
    melee.parentObject = &parentObject;

    this->melees.push_back(melee);

    std::unordered_map<Object *, Damageable *> damageables
        = this->damageRegistry->getDamageables();
    
    for (auto &entry : damageables)
    {
        if (glm::distance(pos, entry.first->transform.position) <= melee.radius
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
            melee->lifespan -= deltaTime;
            melee->object->transform.position = melee->parentObject->transform.position;
        }
    }
}

void MeleeSystem::deleteMelee(Melee *melee, int index)
{
    melee->object->queueFree();
    melees.erase(melees.begin() + index);
}