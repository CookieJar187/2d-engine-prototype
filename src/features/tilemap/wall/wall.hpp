#pragma once

#include "scene.h"
#include "object.h"

struct Wall
{
    Wall(Scene &scene, ObjectCreationData creationData);
    ~Wall();

    glm::ivec2 position;

    bool queuedForDeletion = false;
    void queueFree();

    Object *obj = nullptr;
};