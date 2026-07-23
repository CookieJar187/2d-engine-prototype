#include <iostream>
#include <glm/glm.hpp>

#include "scene.h"

Scene::Scene(CollisionManager &collisionManager, AssetLibrary &assetLibrary)
{
    Scene::collisionManager = &collisionManager;
    Scene::assetLibrary = &assetLibrary;
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

ObjectCreationResult Scene::createObject(const ObjectCreationData &data)
{
    Object2 *newObj = new Object2();

    if (data.name.has_value())
        newObj->name = data.name.value();

    if (data.colliderName.has_value())
        newObj->collider = assetLibrary->getCollider(data.colliderName.value());
    if (data.materialName.has_value())
        newObj->material = assetLibrary->getMaterial(data.materialName.value());

    newObj->mesh = assetLibrary->getMesh();
    newObj->transform = data.transform;

    CollisionEntry *entry = collisionManager->registerObject(*newObj);
    objects.push_back(newObj);

    return {.object = newObj, .collisionEntry = entry};
}