#include <iostream>
#include <glm/glm.hpp>

#include "scene.h"

#include "shader_loader.h"

Scene::Scene(CollisionManager& collisionManager) {
    
    Scene::collisionManager = &collisionManager;

    shader.id = make_shader(
        "src/shaders/vertex2.txt",
        "src/shaders/fragment2.txt"
    );
    shader.modelLoc = glGetUniformLocation(shader.id, "model");
    shader.projectionLoc = glGetUniformLocation(shader.id, "projection");

    material.shader = shader;

    Object2* ground = createObject("ground", AabbCollider{glm::vec2(50, 50)});
    ground->transform.position = glm::vec2(0, -150);
}

void Scene::drawObjects() const
{
    const glm::mat4& projection = Scene::camera.projection;

    for (const auto& obj : objects) {
        obj->draw(projection);
    }
}

std::vector<Object2*> Scene::getObjects()
{ return objects; }

std::vector<Object2*> Scene::getObjectsByName(const std::string& targetName)
{
    std::vector<Object2*> returnVec;

    for (const auto& obj : objects) {
        if (obj->name == targetName)
            returnVec.push_back(obj);
    }

    return returnVec;
}

Object2* Scene::getObjectByName(const std::string& targetName)
{
    for (auto& obj : objects) {
        if (obj->name == targetName)
            return obj;
    }

    return nullptr;
}

Object2* Scene::createObject(const std::string& name, const AabbCollider& collider)
{
    Object2* newObj = new Object2();
    newObj->name = name;
    newObj->collider = collider;
    newObj->mesh = &objMesh;
    newObj->material = &material;
    newObj->transform.position = glm::vec2(0, 0);
    newObj->transform.scale = glm::vec2(100, 100);

    collisionManager->registerObject(*newObj);
    objects.push_back(newObj);

    return newObj;
}