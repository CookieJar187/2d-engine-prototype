#pragma once

#define TILE_SIZE 100
#define MAP_HEIGHT 10
#define MAP_WIDTH 10

#include <vector>
#include <glm/common.hpp>

#include "scene.h"

class Tilemap
{
public:
    Tilemap(Scene &scene);

    void load();

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

    glm::ivec2 getTileFromPosition(const glm::vec2 pos);
    glm::vec2 getPositionFromTile(const glm::ivec2 tile);
};