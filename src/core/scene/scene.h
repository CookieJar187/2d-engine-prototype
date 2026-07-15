#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "object2.h"
#include "mesh_factory.h"
#include "shader.h"
#include "material.h"
#include "camera2.h"

class Scene {
public:
    Shader shader;
    Material material;

    Mesh objMesh = MeshFactory::createSquare();

    Object2 obj1;
    Object2 ground;

    Scene();

    void drawObjects() const;

    std::vector<Object2> getObjects();
    std::vector<Object2> getObjectsByName(const std::string& targetName);
    Object2* getObjectByName(const std::string& targetName);

private:
    std::vector<Object2> objects;
    Camera2 camera;

};