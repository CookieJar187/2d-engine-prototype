#include "tilemap.h"

Tilemap::Tilemap(Scene &scene)
{
    Tilemap::scene = &scene;
}

void Tilemap::load()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (matrix[i][j] == 1)
            {
                ObjectCreationResult wallData = scene->createObject({.name = "wall", .colliderName = "wall", .materialName = "wall"});
                wallData.object->transform.position = glm::vec2(j * TILE_SIZE, -i * TILE_SIZE);
            }
        }
    }
}