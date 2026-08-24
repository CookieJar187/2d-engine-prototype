#pragma once

#define TILE_SIZE 100
#define MAP_HEIGHT 10
#define MAP_WIDTH 10

#include <vector>
#include <optional>
#include <glm/common.hpp>

#include "scene.h"

class Tilemap
{
public:
    Tilemap(Scene &scene);

    void load();

    bool isWalkable(int x, int y);

    glm::ivec2 worldToTile(const glm::vec2& position);
    glm::vec2 tileToWorld(const glm::ivec2& tile);

private:
    Scene *scene;

    Texture wallTexture;
    Material wallMaterial;

    int map[MAP_HEIGHT][MAP_WIDTH] = {
        {0, 0, 0, 0, 1, 1, 0, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 2, 1, 0, 1, 1, 0, 0, 3},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {3, 0, 0, 0, 1, 1, 1, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 3},
        {1, 1, 1, 0, 1, 0, 0, 0, 0, 3},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 2, 2, 1, 1, 2, 2, 1, 1},
    };
};