#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "object2.h"
#include "collision_manager.h"
#include "asset_library.h"

struct ObjectCreationData
{
    std::optional<std::string> name;
    std::optional<std::string> colliderName = "";
    std::optional<std::string> materialName = "";
    Transform2 transform;
};

struct ObjectCreationResult
{
    Object2 *object = nullptr;
    CollisionEntry *collisionEntry = nullptr;
};

class Scene
{
public:
    Scene(CollisionManager &collisionManager, AssetLibrary &assetLibrary);

    void drawObjects(const glm::mat4 &view, const glm::mat4 &projection) const;

    std::vector<Object2 *> getObjects();
    std::vector<Object2 *> getObjectsByName(const std::string &targetName);
    Object2 *getObjectByName(const std::string &targetName);

    ObjectCreationResult createObject(const ObjectCreationData &data);

private:
    AssetLibrary *assetLibrary;
    CollisionManager *collisionManager;
    std::vector<Object2 *> objects;
};