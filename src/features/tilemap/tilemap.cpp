#include "tilemap.h"

Tilemap::Tilemap(Context &ctx)
{
    Tilemap::scene = ctx.scene;
}

void Tilemap::load()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (matrix[i][j] == 1)
            {
                Object *wallObj = scene->createObject({.name = "wall", .colliderName = "wall", .materialName = "wall"});
                wallObj->transform.position = glm::vec2(j * TILE_SIZE, -i * TILE_SIZE);
            }
        }
    }
}