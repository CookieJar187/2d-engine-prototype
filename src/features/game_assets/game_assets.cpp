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
        "player_hit_texture",
        "src/assets/textures/player_hit.png"
    );
    this->resourceManager->addTexture(
        "enemy_texture",
        "src/assets/textures/enemy.png"
    );
    this->resourceManager->addTexture(
        "enemy_hit_texture",
        "src/assets/textures/enemy_hit.png"
    );
    this->resourceManager->addTexture(
        "bullet_texture",
        "src/assets/textures/bullet.png"
    );
    this->resourceManager->addTexture(
        "character_hit_texture",
        "src/assets/textures/characters/character_hit.png"
    );

    // Player textures
    this->resourceManager->addTexture(
        "player_north_texture",
        "src/assets/textures/characters/player_north.png"
    );
    this->resourceManager->addTexture(
        "player_south_texture",
        "src/assets/textures/characters/player_south.png"
    );
    this->resourceManager->addTexture(
        "player_east_texture",
        "src/assets/textures/characters/player_east.png"
    );
    this->resourceManager->addTexture(
        "player_west_texture",
        "src/assets/textures/characters/player_west.png"
    );
    this->resourceManager->addTexture(
        "player_dead1_texture",
        "src/assets/textures/characters/player_dead1.png"
    );
    this->resourceManager->addTexture(
        "player_dead2_texture",
        "src/assets/textures/characters/player_dead2.png"
    );

    // Enemy textures
    this->resourceManager->addTexture(
        "enemy_north_texture",
        "src/assets/textures/characters/enemy_north.png"
    );
    this->resourceManager->addTexture(
        "enemy_south_texture",
        "src/assets/textures/characters/enemy_south.png"
    );
    this->resourceManager->addTexture(
        "enemy_east_texture",
        "src/assets/textures/characters/enemy_east.png"
    );
    this->resourceManager->addTexture(
        "enemy_west_texture",
        "src/assets/textures/characters/enemy_west.png"
    );
    this->resourceManager->addTexture(
        "enemy_dead1_texture",
        "src/assets/textures/characters/enemy_dead1.png"
    );
    this->resourceManager->addTexture(
        "enemy_dead2_texture",
        "src/assets/textures/characters/enemy_dead2.png"
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
        "player_hit_material",
        "sprite_shader",
        "player_hit_texture"
    );
    this->resourceManager->addMaterial(
        "enemy_material",
        "sprite_shader",
        "enemy_texture"
    );
    this->resourceManager->addMaterial(
        "enemy_hit_material",
        "sprite_shader",
        "enemy_hit_texture"
    );
    this->resourceManager->addMaterial(
        "bullet_material",
        "sprite_shader",
        "bullet_texture"
    );
    this->resourceManager->addMaterial(
        "character_hit_material",
        "sprite_shader",
        "character_hit_texture"
    );

    // Player material
    this->resourceManager->addMaterial(
        "player_north_material",
        "sprite_shader",
        "player_north_texture"
    );
    this->resourceManager->addMaterial(
        "player_south_material",
        "sprite_shader",
        "player_south_texture"
    );
    this->resourceManager->addMaterial(
        "player_east_material",
        "sprite_shader",
        "player_east_texture"
    );
    this->resourceManager->addMaterial(
        "player_west_material",
        "sprite_shader",
        "player_west_texture"
    );
    this->resourceManager->addMaterial(
        "player_dead1_material",
        "sprite_shader",
        "player_dead1_texture"
    );
    this->resourceManager->addMaterial(
        "player_dead2_material",
        "sprite_shader",
        "player_dead2_texture"
    );

    // Enemy material
    this->resourceManager->addMaterial(
        "enemy_north_material",
        "sprite_shader",
        "enemy_north_texture"
    );
    this->resourceManager->addMaterial(
        "enemy_south_material",
        "sprite_shader",
        "enemy_south_texture"
    );
    this->resourceManager->addMaterial(
        "enemy_east_material",
        "sprite_shader",
        "enemy_east_texture"
    );
    this->resourceManager->addMaterial(
        "enemy_west_material",
        "sprite_shader",
        "enemy_west_texture"
    );
    this->resourceManager->addMaterial(
        "enemy_dead1_material",
        "sprite_shader",
        "enemy_dead1_texture"
    );
    this->resourceManager->addMaterial(
        "enemy_dead2_material",
        "sprite_shader",
        "enemy_dead2_texture"
    );

    // Colliders
    this->resourceManager->addCollider(
        "character_collider",
        glm::vec2(20, 35)
    );
    this->resourceManager->addCollider(
        "wall",
        glm::vec2(50, 50)
    );
}