#include "object_management.hpp"

#include <algorithm>

void ObjectManagement::cleanupObjects()
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

std::vector<Object *> ObjectManagement::getObjects()
{
    std::vector<Object *> result;

    for (const auto &obj : world->objects)
    {
        result.push_back(obj.get());
    }

    return result;
}

Object *ObjectManagement::getObjectByName(const std::string &targetName)
{
    for (auto &obj : world->objects)
    {
        if (obj->name == targetName)
            return obj.get();
    }

    return nullptr;
}

Object *ObjectManagement::createObject(const ObjectCreationData &data)
{
    auto newObj = std::make_unique<Object>();

    if (data.name.has_value())
        newObj->name = data.name.value();

    if (data.meshId.has_value())
        newObj->mesh = resourceManager->getMesh(data.meshId.value());

    if (data.colliderId.has_value())
        newObj->collider = resourceManager->getCollider(data.colliderId.value());

    if (data.materialId.has_value())
        newObj->material = resourceManager->getMaterial(data.materialId.value());

    newObj->transform = data.transform;

    Object *objectPtr = newObj.get();

    world->objects.push_back(std::move(newObj));
    objectHierarchy->add(world->objects.back().get());

    return objectPtr;
}