#pragma once

#include "world.hpp"
#include "resource_manager.hpp"
#include "object.h"
#include "object_hierarchy.hpp"

struct ObjectCreationData
{
    std::optional<std::string> name = std::nullopt;
    std::optional<std::string> meshId = std::nullopt;
    std::optional<std::string> colliderId = std::nullopt;
    std::optional<std::string> materialId = std::nullopt;
    Transform2 transform;
    Object *parent = nullptr;
};

class ObjectManagement
{
private:
    World *world;
    ResourceManager *resourceManager;
    ObjectHierarchy *objectHierarchy;

public:
    ObjectManagement(World &world, ResourceManager &resourceManager, ObjectHierarchy &objectHierarchy) : world(&world), resourceManager(&resourceManager), objectHierarchy(&objectHierarchy) {}

    void cleanupObjects();

    std::vector<Object *> getObjects();
    Object *getObjectByName(const std::string &targetName);

    Object *createObject(const ObjectCreationData &data);
};