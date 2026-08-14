#include <iostream>
#include <algorithm>

#include "scene.h"

Scene::Scene(World &world, ResourceManager &resourceManager)
{
    this->world = &world;
    this->resourceManager = &resourceManager;
}

void Scene::cleanupObjects()
{
    world->objects.erase(
        std::remove_if(
            world->objects.begin(),
            world->objects.end(),
            [this](const std::unique_ptr<Object> &obj)
            {
                if (!obj->queuedForDeletion)
                    return false;

                return true;
            }),
        world->objects.end());
}

void Scene::drawObjects(const glm::mat4 &view, const glm::mat4 &projection) const
{
    for (const auto &obj : world->objects)
    {
        obj->draw(view, projection);
    }
}

std::vector<Object *> Scene::getObjects()
{
    std::vector<Object *> result;

    for (const auto &obj : world->objects)
    {
        result.push_back(obj.get());
    }

    return result;
}

Object *Scene::getObjectByName(const std::string &targetName)
{
    for (auto &obj : world->objects)
    {
        if (obj->name == targetName)
            return obj.get();
    }

    return nullptr;
}

Object *Scene::createObject(const ObjectCreationData &data)
{
    auto newObj = std::make_unique<Object>();

    if (data.name.has_value())
        newObj->name = data.name.value();

    if (data.colliderName.has_value())
        newObj->collider = resourceManager->getCollider(data.colliderName.value());

    if (data.materialName.has_value())
        newObj->material = resourceManager->getMaterial(data.materialName.value());

    newObj->mesh = resourceManager->getMesh("sprite");
    newObj->transform = data.transform;

    Object *objectPtr = newObj.get();

    world->objects.push_back(std::move(newObj));

    return objectPtr;
}