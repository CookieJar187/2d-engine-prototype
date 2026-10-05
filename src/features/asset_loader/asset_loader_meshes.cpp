#include "asset_loader.hpp"

void AssetLoader::loadMeshes()
{
    this->resourceManager->addQuadMesh(
        "sprite_mesh"
    );
}