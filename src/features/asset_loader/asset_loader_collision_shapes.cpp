#include "asset_loader.hpp"

void AssetLoader::loadCollisionShapes()
{
    // Collision shapes
    this->resourceManager->addAabbShape(
        "character_shape",
        glm::vec2(20, 35)
    );
    this->resourceManager->addAabbShape(
        "wall_shape",
        glm::vec2(50, 50)
    );
    this->resourceManager->addAabbShape(
        "boards_horizontal_shape",
        glm::vec2(50, 10)
    );
    this->resourceManager->addAabbShape(
        "boards_vertical_shape",
        glm::vec2(10, 50)
    );
    this->resourceManager->addAabbShape(
        "tree_shape",
        glm::vec2(40, 30)
    );
}