#pragma once

#include "core.hpp"

class AssetLoader
{
public:
    AssetLoader(Core &core);

private:
    ResourceManager *resourceManager;

    void loadMeshes();
    void loadShaders();
    void loadTextures();
    void loadMaterials();
    void loadCollisionShapes();
    void loadCollisionGroups();
    void loadColliders();
    void loadRaycastFilters();
    void loadSounds();
};