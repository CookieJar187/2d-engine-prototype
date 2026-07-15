#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "mesh.h"
#include "transform2.h"
#include "material.h"

struct Object2 {

public:
    std::string name;

    Mesh* mesh;
    Transform2 transform;
    Material* material;

    //std::vector<Object2> children = {};
    //Object2 parent = NULL;

    Object2(const std::string& name = "object", Mesh* mesh = nullptr, Material* material = nullptr)
        : mesh(mesh), material(material) {}

    void draw(const glm::mat4& projection) const;

private:
    glm::mat4 getModelMatrix() const;

};