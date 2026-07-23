#pragma once

#include <vector>
#include <string>
#include <optional>
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
    std::optional<AabbCollider *> collider = std::nullopt;
    Material *material = nullptr;
    Transform2 transform{};

    void draw(const glm::mat4 &view, const glm::mat4 &projection) const;

private:
    glm::mat4 getModelMatrix() const;
};