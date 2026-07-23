#pragma once

#include "scene.h"

#define TILE_SIZE 100

class Tilemap
{
public:
    Tilemap(Scene &scene);
    void load();

private:
    Scene *scene;

    Texture wallTexture;
    Material wallMaterial;

    int matrix[10][10] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
};