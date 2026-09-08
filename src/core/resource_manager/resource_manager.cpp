#include "resource_manager.hpp"

#include <iostream>

#include "mesh_loader.h"
#include "shader_loader.h"
#include "texture_loader.h"

ResourceManager::ResourceManager()
{
}

// Getter functions
Mesh *ResourceManager::getMesh(const std::string& id)
{
    if (!this->meshes[id])
    {
        std::cerr << "ResourceManager: mesh `" << id << "` not found\n";
        return nullptr;
    }
    return this->meshes[id].get();
}
Shader *ResourceManager::getShader(const std::string& id)
{
    if (!this->shaders[id])
    {
        std::cerr << "ResourceManager: shader `" << id << "` not found\n";
        return nullptr;
    }
    return this->shaders[id].get();
}
Texture *ResourceManager::getTexture(const std::string& id)
{
    if (!this->textures[id])
    {
        std::cerr << "ResourceManager: texture `" << id << "` not found\n";
        return nullptr;
    }
    return this->textures[id].get();
}
Material *ResourceManager::getMaterial(const std::string& id)
{
    if (!this->materials[id])
    {
        std::cerr << "ResourceManager: material `" << id << "` not found\n";
        return nullptr;
    }
    return this->materials[id].get();
}
AabbShape *ResourceManager::getAabbShape(const std::string& id)
{
    if (!this->aabbShapes[id])
    {
        std::cerr << "ResourceManager: aabb shape `" << id << "` not found\n";
        return nullptr;
    }
    return this->aabbShapes[id].get();
}
CollisionGroup* ResourceManager::getCollisionGroup(const std::string& id)
{
    if (!this->collisionGroups[id])
    {
        std::cerr << "ResourceManager: collision group `" << id << "` not found\n";
        return nullptr;
    }
    return this->collisionGroups[id].get();
}
Collider *ResourceManager::getCollider(const std::string& id)
{
    if (!this->collidersss[id])
    {
        std::cerr << "ResourceManager: collider `" << id << "` not found\n";
        return nullptr;
    }
    return this->collidersss[id].get();
}
Sound *ResourceManager::getSound(const std::string& id)
{
    if (!this->sounds[id])
    {
        std::cerr << "ResourceManager: sound `" << id << "` not found\n";
        return nullptr;
    }
    return this->sounds[id].get();
}

// Adder functions
void ResourceManager::addQuadMesh(const std::string& id)
{
    Mesh mesh = MeshLoader::loadQuad();
    this->meshes[id] = std::make_unique<Mesh>(std::move(mesh));
}
void ResourceManager::addMeshFromFile(
    const std::string& id,
    const std::string& path
)
{
    Mesh mesh = MeshLoader::load(path);
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
    try
    {
        Texture texture = TextureLoader::load(path);
        this->textures[id] = std::make_unique<Texture>(std::move(texture));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
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
void ResourceManager::addAabbShape(
    const std::string& id,
    const std::optional<glm::vec2> halfSize
)
{
    AabbShape collider;

    if (halfSize.has_value())
        collider.halfSize = halfSize.value();

    this->aabbShapes[id] = std::make_unique<AabbShape>(std::move(collider));
}

void ResourceManager::addCollisionGroup(
    const std::string& id
)
{
    if (collisionGroups.size() >= 16)
    {
        std::cerr << "ResourceManager: collision group map filled to the brim. ";
        std::cerr << "No more elements can be inserted. Adjust map capacity\n";
        return;
    }

    CollisionGroup group;

    group.id = static_cast<CollisionGroupId>(collisionGroups.size());

    this->collisionGroups[id] = std::make_unique<CollisionGroup>(std::move(group));
}

void ResourceManager::addCollider(
    const std::string& id,
    const std::optional<std::string> aabbShape,
    const std::optional<std::string> collisionGroup
)
{
    Collider collider;

    if (aabbShape.has_value())
        collider.shape = aabbShapes[aabbShape.value()].get();
    if (collisionGroup.has_value())
        collider.group = collisionGroups[collisionGroup.value()].get();

    this->collidersss[id] = std::make_unique<Collider>(std::move(collider));
}

void ResourceManager::addSound(
    const std::string& id,
    const std::string& path
)
{
    try
    {
        std::optional<Sound> newSound = SoundLoader::load(path.c_str());

        if (newSound.has_value())
            this->sounds[id] = std::make_unique<Sound>(std::move(newSound.value()));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

// Setter functions
void ResourceManager::setCollisionGroupRelationship(
    const std::string &id1,
    const std::string &id2
)
{
    CollisionGroup *group1 = getCollisionGroup(id1);
    CollisionGroup *group2 = getCollisionGroup(id2);

    if (group1 == nullptr || group2 == nullptr)
        return;

    uint8_t group1Id = group1->id;
    uint8_t group2Id = group2->id;

    group1->collidesWith |= (1u << group2Id);
    group2->collidesWith |= (1u << group1Id);
}