#include "asset_loader.hpp"

void AssetLoader::loadShaders()
{
    // Shaders
    this->resourceManager->addShader(
        "sprite_shader",
        "src/shaders/vertex2.txt",
        "src/shaders/fragment2.txt"
    );
}