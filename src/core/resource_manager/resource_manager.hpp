#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <optional>

#include <glm/glm.hpp>

#include "texture.h"
#include "shader.h"
#include "material.h"
#include "aabb_collider.h"
#include "mesh.h"
#include "transform2.h"

class ResourceManager
{
public:
    ResourceManager();

    Mesh* getMesh(const std::string& id);
    Shader* getShader(const std::string& id);
    Texture* getTexture(const std::string& id);
    Material* getMaterial(const std::string& id);
    AabbCollider* getCollider(const std::string& id);

    void addMesh(
        const std::string& id);
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
    void addCollider(
        const std::string& id,
        std::optional<glm::vec2> halfSize = std::nullopt);

private:
    std::unordered_map<std::string, std::unique_ptr<Mesh>> meshes;
    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
    std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
    std::unordered_map<std::string, std::unique_ptr<Material>> materials;
    std::unordered_map<std::string, std::unique_ptr<AabbCollider>> colliders;
};