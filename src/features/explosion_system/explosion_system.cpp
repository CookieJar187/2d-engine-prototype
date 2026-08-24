#include "explosion_system.hpp"

#include <iostream>

ExplosionSystem::ExplosionSystem(
    Scene &scene,
    DamageRegistry &damageRegistry
)
{
    this->scene = &scene;
    this->damageRegistry = &damageRegistry;
}

void ExplosionSystem::explode(const glm::vec2 pos)
{
    ObjectCreationData d;
    d.name = "explosion";
    d.meshId = "sprite_mesh";
    d.materialId = "explosion_material";
    d.transform = { .position = pos, .scale = {200.0f, 200.0f} };

    Explosion expl;
    expl.object = this->scene->createObject(d);

    this->explosions.push_back(expl);

    std::unordered_map<Object *, Damageable *> damageables
        = this->damageRegistry->getDamageables();

    for (auto &entry : damageables)
    {
        if (glm::distance(pos, entry.first->transform.position) <= expl.radius)
        {
            entry.second->takeDamage(100);
        }
    }
}

void ExplosionSystem::update(float deltaTime)
{
    for (int i = explosions.size() - 1; i >= 0; i--)
    {
        Explosion *expl = &explosions[i];

        if (expl->lifespan <= 0)
            deleteExplosion(expl, i);
        else
            expl->lifespan -= deltaTime;
    }
}

void ExplosionSystem::deleteExplosion(Explosion *expl, int index)
{
    expl->object->queueFree();
    explosions.erase(explosions.begin() + index);
}