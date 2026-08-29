#include "explosion_system.hpp"

#include <iostream>

#include "rng.hpp"

ExplosionSystem::ExplosionSystem(
    Scene &scene,
    DamageRegistry &damageRegistry,
    CameraShaker &cameraShaker,
    ResourceManager &resourceManager
)
{
    this->scene = &scene;
    this->damageRegistry = &damageRegistry;
    this->cameraShaker = &cameraShaker;

    this->explosion1Sound = resourceManager.getSound("explosion1_sound");
    this->explosion2Sound = resourceManager.getSound("explosion2_sound");
    this->explosion3Sound = resourceManager.getSound("explosion3_sound");
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

    this->cameraShaker->explosionShake();

    int randSound = rng::getInt(2);
    if (randSound == 0)
        this->explosion1Sound->play();
    else if (randSound == 1)
        this->explosion2Sound->play();
    else
        this->explosion3Sound->play();
    
    for (auto &entry : damageables)
    {
        if (glm::distance(pos, entry.first->transform.position) <= expl.radius)
        {
            entry.second->takeDamage(500);
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