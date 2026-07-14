#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "object2.h"
#include "mesh_factory.h"
#include "shader.h"
#include "material.h"

class Scene {

public:
    std::vector<Object2> objects;

    Shader shader;
    Material material;

    Mesh objMesh = MeshFactory::createSquare();

    Object2 obj1;
    Object2 ground;

    Scene();

    void draw(const glm::mat4& projection) const;

};