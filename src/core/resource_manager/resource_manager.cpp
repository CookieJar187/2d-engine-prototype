#include "resource_manager.hpp"

#include "mesh_factory.h"
#include "shader_loader.h"
#include "texture_loader.h"

ResourceManager::ResourceManager()
{
}

// GET
Mesh *ResourceManager::getMesh(const std::string& id)
{
    if (!this->meshes[id])
        return nullptr;
    return this->meshes[id].get();
}
Shader *ResourceManager::getShader(const std::string& id)
{
    if (!this->shaders[id])
        return nullptr;
    return this->shaders[id].get();
}
Texture *ResourceManager::getTexture(const std::string& id)
{
    if (!this->textures[id])
        return nullptr;
    return this->textures[id].get();
}
Material *ResourceManager::getMaterial(const std::string& id)
{
    if (!this->materials[id])
        return nullptr;
    return this->materials[id].get();
}
AabbCollider *ResourceManager::getCollider(const std::string& id)
{
    if (!this->colliders[id])
        return nullptr;
    return this->colliders[id].get();
}

// SET
void ResourceManager::addMesh(const std::string& id)
{
    Mesh mesh = MeshFactory::createSquare();
    this->meshes[id] = std::make_unique<Mesh>(std::move(mesh));
}
void ResourceManager::addShader(
    const std::string& id,
    const std::string& vertexShaderPath,
    const std::string& fragmentShaderPath
)
{
    Shader shader;
    shader.id = make_shader(vertexShaderPath, fragmentShaderPath);

    shader.modelLoc = glGetUniformLocation(shader.id, "model");
    shader.viewLoc = glGetUniformLocation(shader.id, "view");
    shader.projectionLoc = glGetUniformLocation(shader.id, "projection");
    shader.textureLoc = glGetUniformLocation(shader.id, "spriteTexture");

    this->shaders[id] = std::make_unique<Shader>(std::move(shader));
}
void ResourceManager::addTexture(
    const std::string& id,
    const std::string& path
)
{
    Texture texture = TextureLoader::load(path);
    this->textures[id] = std::make_unique<Texture>(std::move(texture));
}
void ResourceManager::addMaterial(
    const std::string& id,
    const std::optional<std::string> shader,
    const std::optional<std::string> texture
)
{
    Material material;

    if (shader.has_value() && shaders[shader.value()])
        material.shader = shaders[shader.value()].get();
    if (texture.has_value() && textures[texture.value()])
        material.texture = textures[texture.value()].get();

    this->materials[id] = std::make_unique<Material>(std::move(material));
}
void ResourceManager::addCollider(
    const std::string& id,
    const std::optional<glm::vec2> halfSize
)
{
    AabbCollider collider;

    if (halfSize.has_value())
        collider.halfSize = halfSize.value();

    this->colliders[id] = std::make_unique<AabbCollider>(std::move(collider));
}