#include <iostream>
#include <glm/glm.hpp>

#include "scene.h"

#include "shader_loader.h"

Scene::Scene(CollisionManager &collisionManager)
{
    Scene::collisionManager = &collisionManager;

    shader.id = make_shader(
        "src/shaders/vertex2.txt",
        "src/shaders/fragment2.txt");
    shader.modelLoc = glGetUniformLocation(shader.id, "model");
    shader.viewLoc = glGetUniformLocation(shader.id, "view");
    shader.projectionLoc = glGetUniformLocation(shader.id, "projection");

    material.shader = shader;
}

void Scene::drawObjects(const glm::mat4 &view, const glm::mat4 &projection) const
{
    for (const auto &obj : objects)
    {
        obj->draw(view, projection);
    }
}

std::vector<Object2 *> Scene::getObjects()
{
    return objects;
}

std::vector<Object2 *> Scene::getObjectsByName(const std::string &targetName)
{
    std::vector<Object2 *> returnVec;

    for (const auto &obj : objects)
    {
        if (obj->name == targetName)
            returnVec.push_back(obj);
    }

    return returnVec;
}

Object2 *Scene::getObjectByName(const std::string &targetName)
{
    for (auto &obj : objects)
    {
        if (obj->name == targetName)
            return obj;
    }

    return nullptr;
}

ObjectCreationResult Scene::createObject(const std::string &name, const AabbCollider &collider)
{
    Object2 *newObj = new Object2();
    newObj->name = name;
    newObj->collider = collider;
    newObj->mesh = &objMesh;
    newObj->material = &material;
    newObj->transform.position = glm::vec2(0, 0);
    newObj->transform.scale = glm::vec2(100, 100);

    CollisionEntry *entry = collisionManager->registerObject(*newObj);
    objects.push_back(newObj);

    return {.object = newObj, .collisionEntry = entry};
}