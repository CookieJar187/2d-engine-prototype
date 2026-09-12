#include "scene.hpp"

#include <algorithm>

void Scene::relocateSubTree(Object &object, uint8_t newGeneration)
{
    uint8_t oldGeneration = object.generation;

    if (oldGeneration != newGeneration)
    {
        if (world->hierarchy.size() <= newGeneration)
            world->hierarchy.resize(newGeneration + 1);

        auto &oldBucket = world->hierarchy[oldGeneration];

        auto it = std::find_if(
            oldBucket.begin(),
            oldBucket.end(),
            [&object](const std::unique_ptr<Object> &ptr)
            {
                return ptr.get() == &object;
            });

        if (it == oldBucket.end())
            return;

        auto movedObject = std::move(*it);

        oldBucket.erase(it);

        object.generation = newGeneration;

        world->hierarchy[newGeneration].push_back(std::move(movedObject));
    }

    for (Object *child : object.children)
    {
        relocateSubTree(
            *child,
            object.generation + 1);
    }
}

void Scene::reparent(Object &object, size_t oldGeneration, size_t objectIndex)
{
    Object *oldParent = object.parent;
    Object *newParent = object.requestedParent;

    if (oldParent != nullptr)
        std::erase(oldParent->children, &object);

    object.parent = newParent;

    if (newParent != nullptr)
        newParent->children.push_back(&object);

    uint8_t newGeneration = 0;

    if (newParent != nullptr)
        newGeneration = newParent->generation + 1;

    //
    if (world->hierarchy.size() <= newGeneration)
        world->hierarchy.resize(newGeneration + 1);

    auto movedObject = std::move(world->hierarchy[oldGeneration][objectIndex]);

    world->hierarchy[oldGeneration].erase(
        world->hierarchy[oldGeneration].begin() + objectIndex);

    object.generation = newGeneration;

    world->hierarchy[newGeneration].push_back(std::move(movedObject));

    //
    for (Object *child : object.children)
    {
        relocateSubTree(*child, object.generation + 1);
    }

    object.requestedParent = nullptr;
    object.parentChangeQueued = false;
}

void Scene::process()
{
    for (size_t g = 0; g < world->hierarchy.size(); ++g)
    {
        for (size_t i = world->hierarchy[g].size(); i-- > 0;)
        {
            Object &object = *world->hierarchy[g][i];

            if (object.queuedForDeletion)
            {
                world->hierarchy[g].erase(
                    world->hierarchy[g].begin() + i);
            }
            else if (object.parentChangeQueued)
            {
                reparent(object, g, i);
            }
        }
    }

    while (!world->hierarchy.empty() && world->hierarchy.back().empty())
    {
        world->hierarchy.pop_back();
    }
}

std::vector<Object *> Scene::getObjects()
{
    std::vector<Object *> result;

    for (auto &generation : world->hierarchy)
    {
        for (const auto &obj : generation)
        {
            result.push_back(obj.get());
        }
    }

    return result;
}

Object *Scene::getObjectByName(const std::string &targetName)
{
    for (auto &generation : world->hierarchy)
    {
        for (auto &obj : generation)
        {
            if (obj->name == targetName)
                return obj.get();
        }
    }

    return nullptr;
}

Object *Scene::createObject(const ObjectCreationData &data)
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
    newObj->parent = data.parent;

    //
    uint8_t generation = 0;

    if (data.parent != nullptr)
        generation = data.parent->generation + 1;

    newObj->generation = generation;

    Object *objectPtr = newObj.get();

    if (world->hierarchy.size() <= generation)
        world->hierarchy.resize(generation + 1);

    world->hierarchy[generation].push_back(std::move(newObj));

    return objectPtr;
}