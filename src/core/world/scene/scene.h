#pragma once

#include <optional>
#include <glm/glm.hpp>

#include "world.h"
#include "resource_manager.hpp"

struct ObjectCreationData
{
    std::optional<std::string> name;
    std::optional<std::string> colliderName = "";
    std::optional<std::string> materialName = "";
    Transform2 transform;
};

class Scene
{
public:
    Scene(World &world, ResourceManager &resourceManager);

    void cleanupObjects();
    void drawObjects(const glm::mat4 &view, const glm::mat4 &projection) const;

    std::vector<Object *> getObjects();
    Object *getObjectByName(const std::string &targetName);

    Object *createObject(const ObjectCreationData &data);

private:
    World *world;
    ResourceManager *resourceManager;
};