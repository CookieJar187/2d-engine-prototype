#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "mesh.h"
#include "collider.hpp"
#include "transform2.h"
#include "material.h"

class ObjectHierarchy;

struct Object
{
public:
    std::string name = "object";
    Mesh *mesh = nullptr;
    Collider *collider = nullptr;
    Material *material = nullptr;
    Transform2 transform{};

    bool queuedForDeletion = false;

    Object *getParent() const;
    void setParent(Object *newParent);

    void queueFree();
    void draw(const glm::mat4 &view, const glm::mat4 &projection) const;

    friend class ObjectHierarchy;

private:
    glm::mat4 getModelMatrix() const;

    Object *parent = nullptr;
    std::vector<Object *> children;
    uint8_t generation = 0;
};