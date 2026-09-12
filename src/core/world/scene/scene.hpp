#pragma once

#include <vector>

#include "world.hpp"
#include "resource_manager.hpp"

struct ObjectCreationData
{
    std::optional<std::string> name = std::nullopt;
    std::optional<std::string> meshId = std::nullopt;
    std::optional<std::string> colliderId = std::nullopt;
    std::optional<std::string> materialId = std::nullopt;
    Transform2 transform;
    Object *parent = nullptr;
};

class Scene
{
public:
    Scene(World &world, ResourceManager &resourceManager)
    : world(&world), resourceManager(&resourceManager) {}

    void process();

    std::vector<Object *> getObjects();
    
    Object *getObjectByName(const std::string &targetName);

    Object *createObject(const ObjectCreationData &data);

private:
    World *world;
    ResourceManager *resourceManager;

    void relocateSubTree(Object &object, uint8_t newGeneration);
    void reparent(Object &object, size_t oldGeneration, size_t objectIndex);
};