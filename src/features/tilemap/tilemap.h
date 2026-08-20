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
    std::optional<glm::ivec2> getTileFromPosition(glm::vec2 &pos);

private:
    Scene *scene;

    Texture wallTexture;
    Material wallMaterial;

    int map[MAP_HEIGHT][MAP_WIDTH] = {
        {0, 0, 0, 0, 1, 1, 0, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 1, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
};