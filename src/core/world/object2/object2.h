#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "mesh.h"
#include "aabb_collider.h"
#include "transform2.h"
#include "material.h"

struct Object2
{
public:
    std::string name = "object";
    Mesh *mesh = nullptr;
    AabbCollider *collider = nullptr;
    Material *material = nullptr;
    Transform2 transform{};

    bool queuedForDeletion = false;

    void queueFree();
    void draw(const glm::mat4 &view, const glm::mat4 &projection) const;

private:
    glm::mat4 getModelMatrix() const;
};