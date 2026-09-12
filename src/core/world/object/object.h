#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "mesh.h"
#include "collider.hpp"
#include "transform2.h"
#include "material.h"

class Scene;
class Renderer;

struct Object
{
public:
    std::string name = "object";
    Mesh *mesh = nullptr;
    Collider *collider = nullptr;
    Material *material = nullptr;
    Transform2 transform{};

    uint8_t generation = 0;

    bool queuedForDeletion = false;
    bool parentChangeQueued = false;
    Object *requestedParent = nullptr;

    Object *getParent() const;
    void setParent(Object *newParent);

    void queueFree();

    friend class Scene;
    friend class Renderer;

private:

    Object *parent = nullptr;
    std::vector<Object *> children;

    glm::mat4 worldMatrix{1.0f};
};