#include <iostream>
#include <glm/glm.hpp>

#include "scene.h"

#include "shader_loader.h"

Scene::Scene() {
    
    shader.id = make_shader(
        "src/shaders/vertex2.txt",
        "src/shaders/fragment2.txt"
    );
    shader.modelLoc = glGetUniformLocation(shader.id, "model");
    shader.projectionLoc = glGetUniformLocation(shader.id, "projection");

    material.shader = shader;

    obj1.mesh = &objMesh;
    obj1.material = &material;
    obj1.transform.position = glm::vec2(0, 0);
    obj1.transform.scale = glm::vec2(100, 100);
    obj1.name = "player";

    ground.mesh = &objMesh;
    ground.material = &material;
    ground.transform.position = glm::vec2(0, -150);
    ground.transform.scale = glm::vec2(300, 50);

    objects.push_back(obj1);
    objects.push_back(ground);

}

void Scene::drawObjects() const
{
    const glm::mat4& projection = Scene::camera.projection;

    for (const auto& obj : objects) {
        obj.draw(projection);
    }
}

std::vector<Object2> Scene::getObjects()
{ return objects; }

std::vector<Object2> Scene::getObjectsByName(const std::string& targetName)
{
    std::vector<Object2> returnVec;

    for (const auto& obj : objects) {
        if (obj.name == targetName)
            returnVec.push_back(obj);
    }

    return returnVec;
}

Object2* Scene::getObjectByName(const std::string& targetName)
{
    for (auto& obj : objects) {
        if (obj.name == targetName)
            return &obj;
    }

    return nullptr;
}