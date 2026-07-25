#pragma once

#include <string>
#include <unordered_map>

#include "mesh.h"
#include "material.h"
#include "aabb_collider.h"

class AssetLibrary
{
private:
    std::unordered_map<std::string, Material *> materials;
    std::unordered_map<std::string, AabbCollider *> colliders;

    Material *fallbackMaterial = nullptr;

    // Assets
    Shader shader;

    Mesh quadMesh;

    Texture placeholderTexture;
    Texture wallTexture;
    Texture playerTexture;
    Texture enemyTexture;

    Material placeholderMaterial;
    Material wallMaterial;
    Material playerMaterial;
    Material enemyMaterial;

    AabbCollider playerCollider;
    AabbCollider wallCollider;
    AabbCollider enemyCollider;

public:
    AssetLibrary();

    Material *getMaterial(const std::string &name) const;
    AabbCollider *getCollider(const std::string &name) const;
    Mesh *getMesh();
};