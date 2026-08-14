#include "game_assets.hpp"

GameAssets::GameAssets(ResourceManager &resourceManager)
{
    this->resourceManager = &resourceManager;

    // Shaders
    this->resourceManager->addShader(
        "sprite",
        "src/shaders/vertex2.txt",
        "src/shaders/fragment2.txt");
        
    // Meshes
    this->resourceManager->addMesh(
        "sprite"
    );

    // Textures
    this->resourceManager->addTexture(
        "placeholder",
        "src/assets/textures/placeholder.png"
    );
    this->resourceManager->addTexture(
        "bricks",
        "src/assets/textures/bricks.png"
    );
    this->resourceManager->addTexture(
        "player",
        "src/assets/textures/player.png"
    );
    this->resourceManager->addTexture(
        "enemy",
        "src/assets/textures/enemy.png"
    );
    this->resourceManager->addTexture(
        "bullet",
        "src/assets/textures/bullet.png"
    );

    // Materials
    this->resourceManager->addMaterial(
        "placeholder",
        "sprite",
        "placeholder"
    );
    this->resourceManager->addMaterial(
        "bricks",
        "sprite",
        "bricks"
    );
    this->resourceManager->addMaterial(
        "player",
        "sprite",
        "player"
    );
    this->resourceManager->addMaterial(
        "enemy",
        "sprite",
        "enemy"
    );
    this->resourceManager->addMaterial(
        "bullet",
        "sprite",
        "bullet"
    );

    // Colliders
    this->resourceManager->addCollider(
        "player",
        glm::vec2(40, 40)
    );
    this->resourceManager->addCollider(
        "enemy",
        glm::vec2(40, 40)
    );
    this->resourceManager->addCollider(
        "wall",
        glm::vec2(50, 50)
    );
}