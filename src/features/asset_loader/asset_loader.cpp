#include "asset_loader.hpp"

AssetLoader::AssetLoader(Core &core)
{
    this->resourceManager = &core.resourceManager;

    loadMeshes();
    loadShaders();
    loadTextures();
    loadMaterials();
    loadCollisionShapes();
    loadCollisionGroups();
    loadColliders();
    loadRaycastFilters();
    loadSounds();
}