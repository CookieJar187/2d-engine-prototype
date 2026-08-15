#include "game_assets.hpp"

GameAssets::GameAssets(ResourceManager &resourceManager)
{
    this->resourceManager = &resourceManager;

    // Shaders
    this->resourceManager->addShader(
        "sprite_shader",
        "src/shaders/vertex2.txt",
        "src/shaders/fragment2.txt");
        
    // Meshes
    this->resourceManager->addQuadMesh(
        "sprite_mesh"
    );

    // Textures
    this->resourceManager->addTexture(
        "placeholder_texture",
        "src/assets/textures/placeholder.png"
    );
    this->resourceManager->addTexture(
        "bricks_texture",
        "src/assets/textures/bricks.png"
    );
    this->resourceManager->addTexture(
        "player_texture",
        "src/assets/textures/player.png"
    );
    this->resourceManager->addTexture(
        "enemy_texture",
        "src/assets/textures/enemy.png"
    );
    this->resourceManager->addTexture(
        "bullet_texture",
        "src/assets/textures/bullet.png"
    );

    // Materials
    this->resourceManager->addMaterial(
        "placeholder_material",
        "sprite_shader",
        "placeholder_texture"
    );
    this->resourceManager->addMaterial(
        "bricks_material",
        "sprite_shader",
        "bricks_texture"
    );
    this->resourceManager->addMaterial(
        "player_material",
        "sprite_shader",
        "player_texture"
    );
    this->resourceManager->addMaterial(
        "enemy_material",
        "sprite_shader",
        "enemy_texture"
    );
    this->resourceManager->addMaterial(
        "bullet_material",
        "sprite_shader",
        "bullet_texture"
    );

    // Colliders
    this->resourceManager->addCollider(
        "character_collider",
        glm::vec2(40, 40)
    );
    this->resourceManager->addCollider(
        "wall",
        glm::vec2(50, 50)
    );
}