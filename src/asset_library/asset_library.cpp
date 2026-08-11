#include "asset_library.h"

#include "shader.h"
#include "texture.h"
#include "texture_loader.h"
#include "shader_loader.h"
#include "mesh_factory.h"

AssetLibrary::AssetLibrary()
{
    // Shader
    shader.id = make_shader("src/shaders/vertex2.txt", "src/shaders/fragment2.txt");

    shader.modelLoc = glGetUniformLocation(shader.id, "model");
    shader.viewLoc = glGetUniformLocation(shader.id, "view");
    shader.projectionLoc = glGetUniformLocation(shader.id, "projection");
    shader.textureLoc = glGetUniformLocation(shader.id, "spriteTexture");

    // Mesh
    quadMesh = MeshFactory::createSquare();

    // Texture
    placeholderTexture = TextureLoader::load("src/assets/textures/placeholder.png");
    wallTexture = TextureLoader::load("src/assets/textures/bricks.png");
    playerTexture = TextureLoader::load("src/assets/textures/player.png");
    enemyTexture = TextureLoader::load("src/assets/textures/enemy.png");
    bulletTexture = TextureLoader::load("src/assets/textures/bullet.png");

    // Material
    placeholderMaterial.shader = &shader;
    placeholderMaterial.texture = &placeholderTexture;

    wallMaterial.shader = &shader;
    wallMaterial.texture = &wallTexture;

    playerMaterial.shader = &shader;
    playerMaterial.texture = &playerTexture;

    enemyMaterial.shader = &shader;
    enemyMaterial.texture = &enemyTexture;

    bulletMaterial.shader = &shader;
    bulletMaterial.texture = &bulletTexture;

    // Aabb colliders
    playerCollider.halfSize = glm::vec2(40, 40);
    playerCollider.name = "player";

    enemyCollider.halfSize = glm::vec2(40, 40);
    playerCollider.name = "enemy";

    wallCollider.halfSize = glm::vec2(50, 50);
    playerCollider.name = "wall";

    // Making assets accessible
    materials["placeholder"] = &placeholderMaterial;
    materials["wall"] = &wallMaterial;
    materials["player"] = &playerMaterial;
    materials["enemy"] = &enemyMaterial;
    materials["bullet"] = &bulletMaterial;

    colliders["player"] = &playerCollider;
    colliders["enemy"] = &enemyCollider;
    colliders["wall"] = &wallCollider;

    // Fallback placeholder (in case of an error)
    fallbackMaterial = &placeholderMaterial;
}

Material *AssetLibrary::getMaterial(const std::string &name) const
{
    auto found = materials.find(name);

    if (found == materials.end())
        return fallbackMaterial;

    return found->second;
}

AabbCollider *AssetLibrary::getCollider(const std::string &name) const
{
    auto found = colliders.find(name);

    if (found == colliders.end())
        return nullptr;

    return found->second;
}

Mesh *AssetLibrary::getMesh()
{
    return &quadMesh;
}