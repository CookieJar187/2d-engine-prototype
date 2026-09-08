#include "grenade_system.hpp"

#include <iostream>
#include <algorithm>

GrenadeSystem::GrenadeSystem(
    Core &core,
    ExplosionSystem &explosionSystem
)
{
    this->scene = &core.scene;
    this->collision = &core.collision;
    this->explosionSystem = &explosionSystem;

    this->grenadeOn = core.resourceManager.getMaterial("grenade_on_material");
    this->grenadeOff = core.resourceManager.getMaterial("grenade_off_material");

    this->grenadeBeep = core.resourceManager.getSound("grenade_beep_sound");

    CollisionGroup *obstacleCollisionGroup = core.resourceManager.getCollisionGroup("obstacle_collision_group");

    this->raycastFilter.groups = (1u << obstacleCollisionGroup->id);
    this->raycastFilter.mode = GroupFilterMode::PermitOnly;
}

void GrenadeSystem::launch(
    const glm::vec2 origin,
    const glm::vec2 dir
)
{
    ObjectCreationData d;
    d.name = "grenade";
    d.meshId = "sprite_mesh";
    d.materialId = "grenade_off_material";
    d.transform = { .position = origin };

    Grenade grnd;
    grnd.position = origin;
    grnd.direction = dir;
    grnd.object = this->scene->createObject(d);

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
            grnd->tickElapsed += deltaTime;

            if (grnd->tickElapsed > grnd->nextTick)
            {
                grnd->tickElapsed = 0.0f;
                grnd->nextTick *= 0.8f;
                grnd->nextTick = std::clamp(grnd->nextTick, GRENADE_MIN_TICK_FREQ, 1.0f);

                if (grnd->tickState == 1)
                {
                    grnd->object->material = this->grenadeOn;
                    grnd->tickState = 0;
                    this->grenadeBeep->play();
                }
                else
                {
                    grnd->object->material = this->grenadeOff;
                    grnd->tickState = 1;
                    this->grenadeBeep->play();
                }
            }
            
            float temp = grnd->momentum * 0.9;
            if (temp < 0.01f)
                grnd->momentum = 0.0f;
            else
            {
                grnd->momentum = temp;
                glm::vec2 targetPos = grnd->position + (grnd->direction * grnd->momentum);

                std::optional<RaycastHit> hit = this->collision->raycast(
                    grnd->position,
                    targetPos,
                    this->raycastFilter
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