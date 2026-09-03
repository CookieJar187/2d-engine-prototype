#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <optional>

#include <glm/glm.hpp>

#include "texture.h"
#include "shader.h"
#include "material.h"
#include "aabb_shape.hpp"
#include "collider.hpp"
#include "collision_group.hpp"
#include "mesh.h"
#include "transform2.h"
#include "sound_loader.hpp"
#include "sound.hpp"

class ResourceManager
{
public:
    ResourceManager();

    // Getter functions
    Mesh* getMesh(const std::string& id);
    Shader* getShader(const std::string& id);
    Texture* getTexture(const std::string& id);
    Material* getMaterial(const std::string& id);
    AabbShape* getAabbShape(const std::string& id);
    CollisionGroup* getCollisionGroup(const std::string& id);
    Collider* getCollider(const std::string& id);
    Sound* getSound(const std::string& id);

    // Adder functions
    void addQuadMesh(
        const std::string& id);
    void addMeshFromFile(
        const std::string& id,
        const std::string& path);
    void addShader(
        const std::string& id,
        const std::string& vertexShaderPath,
        const std::string& fragmentShaderPath);
    void addTexture(
        const std::string& id,
        const std::string& path);
    void addMaterial(
        const std::string& id,
        const std::optional<std::string> shader = std::nullopt,
        const std::optional<std::string> texture = std::nullopt);
    void addAabbShape(
        const std::string& id,
        std::optional<glm::vec2> halfSize = std::nullopt);
    void addCollisionGroup(
        const std::string& id);
    void addCollider(
        const std::string& id,
        const std::optional<std::string> aabbShape = std::nullopt,
        const std::optional<std::string> collisionGroup = std::nullopt);
    void addSound(
        const std::string& id,
        const std::string& path);

    // Setter functions
    void setCollisionGroupRelationship(
        const std::string& id1,
        const std::string& id2,
        const bool value
    );

private:
    std::unordered_map<std::string, std::unique_ptr<Mesh>> meshes;
    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
    std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
    std::unordered_map<std::string, std::unique_ptr<Material>> materials;
    std::unordered_map<std::string, std::unique_ptr<AabbShape>> aabbShapes;
    std::unordered_map<std::string, std::unique_ptr<CollisionGroup>> collisionGroups;
    std::unordered_map<std::string, std::unique_ptr<Collider>> collidersss;
    std::unordered_map<std::string, std::unique_ptr<Sound>> sounds;
};