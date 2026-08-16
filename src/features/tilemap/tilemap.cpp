#include "tilemap.h"

#include <iostream>

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
            if (map[i][j] == 1)
            {
                Object *wallObj = scene->createObject({
                    .name = "wall",
                    .meshId = "sprite_mesh",
                    .colliderId = "wall",
                    .materialId = "bricks_material"});

                wallObj->transform.position = glm::vec2(j * TILE_SIZE, -i * TILE_SIZE);
            }
        }
    }
}

glm::ivec2 Tilemap::getTileFromPosition(const glm::vec2 pos)
{
    glm::ivec2 m;
    m.x = pos.x / TILE_SIZE;
    m.y = -pos.y / TILE_SIZE;
    return m;
}

glm::vec2 Tilemap::getPositionFromTile(const glm::ivec2 pos)
{
    return pos;
}