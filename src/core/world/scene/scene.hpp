#pragma once

#include "object_hierarchy.hpp"
#include "object_management.hpp"

class Scene
{
public:
    Scene(World &world, ResourceManager &resourceManager)
    : world(&world), resourceManager(&resourceManager) {}

    void cleanupObjects();

    std::vector<Object *> getObjects();
    
    Object *getObjectByName(const std::string &targetName);

    Object *createObject(const ObjectCreationData &data);

private:
    World *world;
    ResourceManager *resourceManager;

    ObjectHierarchy objectHierarchy{};
    ObjectManagement objectManagement{*world, *resourceManager, objectHierarchy};
};