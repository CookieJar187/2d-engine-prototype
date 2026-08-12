#include <iostream>
#include <algorithm>
#include <glm/glm.hpp>

#include "scene.h"

Scene::Scene(CollisionManager &collisionManager, AssetLibrary &assetLibrary)
{
    Scene::collisionManager = &collisionManager;
    Scene::assetLibrary = &assetLibrary;
}

void Scene::cleanupObjects()
{
    objects.erase(
        std::remove_if(
            objects.begin(),
            objects.end(),
            [this](const std::unique_ptr<Object2> &obj)
            {
                if (!obj->queuedForDeletion)
                    return false;

                collisionManager->unregisterObject(*obj);

                return true;
            }),
        objects.end());
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
    std::vector<Object2 *> result;

    for (const auto &obj : objects)
    {
        result.push_back(obj.get());
    }

    return result;
}

Object2 *Scene::getObjectByName(const std::string &targetName)
{
    for (auto &obj : objects)
    {
        if (obj->name == targetName)
            return obj.get();
    }

    return nullptr;
}

ObjectCreationResult Scene::createObject(const ObjectCreationData &data)
{
    auto newObj = std::make_unique<Object2>();

    if (data.name.has_value())
        newObj->name = data.name.value();

    if (data.colliderName.has_value())
        newObj->collider = assetLibrary->getCollider(data.colliderName.value());

    if (data.materialName.has_value())
        newObj->material = assetLibrary->getMaterial(data.materialName.value());

    newObj->mesh = assetLibrary->getMesh();
    newObj->transform = data.transform;

    Object2 *objectPtr = newObj.get();

    CollisionEntry *entry = collisionManager->registerObject(*newObj);

    objects.push_back(std::move(newObj));

    return {.object = objectPtr, .collisionEntry = entry};
}