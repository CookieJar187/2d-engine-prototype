#include "debug_points.hpp"

DebugPoints::DebugPoints(Core &core)
{
    this->scene = &core.scene;
    this->resourceManager = &core.resourceManager;
}

void DebugPoints::update(float deltaTime)
{
    for (int i = points.size() - 1; i >= 0; i--)
    {
        if (points[i].lifetime <= 0)
        {
            points[i].object->queueFree();
            points.erase(points.begin() + i);
        }
        else
        {
            points[i].lifetime -= deltaTime;
        }
    }
}

void DebugPoints::newPoint(glm::vec2 pos)
{
    Object *newObject = scene->createObject(
        {
            .name = "debug_point",
            .meshId = "sprite_mesh",
            .materialId = "debug_point_material",
            .transform = {.position = pos, .scale = {12.5, 12.5}}
        }
    );

    DebugPoint newPoint;
    newPoint.object = newObject;

    points.push_back(newPoint);
}