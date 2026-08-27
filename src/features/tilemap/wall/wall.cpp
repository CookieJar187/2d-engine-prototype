#include "wall.hpp"

Wall::Wall(Scene &scene, ObjectCreationData creationData)
{
    this->obj = scene.createObject(creationData);
}

Wall::~Wall()
{
    if (this->obj != nullptr)
        this->obj->queueFree();
}

void Wall::queueFree()
{
    queuedForDeletion = true;
}