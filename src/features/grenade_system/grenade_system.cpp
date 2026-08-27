#include "grenade_system.hpp"

#include <iostream>

GrenadeSystem::GrenadeSystem(
    Scene &scene,
    CollisionManager &collisionManager,
    ExplosionSystem &explosionSystem
)
{
    this->scene = &scene;
    this->collisionManager = &collisionManager;
    this->explosionSystem = &explosionSystem;
}

void GrenadeSystem::launch(
    const glm::vec2 origin,
    const glm::vec2 dir,
    Object *launcher
)
{
    ObjectCreationData d;
    d.name = "grenade";
    d.meshId = "sprite_mesh";
    d.materialId = "grenade_on_material";
    d.transform = { .position = origin };

    Grenade grnd;
    grnd.position = origin;
    grnd.direction = dir;
    grnd.object = this->scene->createObject(d);
    grnd.launcher = launcher;

    this->grenades.push_back(grnd);
}

void GrenadeSystem::update(float deltaTime)
{
    for (int i = grenades.size() - 1; i >= 0; i--)
    {
        Grenade *grnd = &grenades[i];

        if (grnd->lifespan <= 0)
        {
            this->explosionSystem->explode(grnd->position);
            deleteGrenade(grnd, i);
        }
        else
        {
            grnd->lifespan -= deltaTime;
            
            float temp = grnd->momentum * 0.9;
            if (temp < 0.01f)
                grnd->momentum = 0.0f;
            else
            {
                grnd->momentum = temp;
                glm::vec2 targetPos = grnd->position + (grnd->direction * grnd->momentum);

                std::optional<RaycastHit> hit = this->collisionManager->raycast(
                    grnd->position,
                    targetPos,
                    grnd->launcher
                );

                if (hit.has_value())
                {
                    grnd->direction = glm::reflect(
                        grnd->direction,
                        hit->normal
                    );

                    grnd->position = hit.value().point + hit.value().normal * 0.1f;
                    grnd->object->transform.position = grnd->position;
                }
                else
                {
                    grnd->position = targetPos;
                    grnd->object->transform.position = grnd->position;
                }
            }
        }
    }
}

void GrenadeSystem::deleteGrenade(Grenade *grnd, int index)
{
    grnd->object->queueFree();
    grenades.erase(grenades.begin() + index);
}