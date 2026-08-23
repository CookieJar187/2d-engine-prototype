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

bool Tilemap::isWalkable(int x, int y)
{
    bool value = map[y][x] == 0;
    return value;
}

glm::ivec2 Tilemap::worldToTile(const glm::vec2& position)
{
    return {
        static_cast<int>(std::floor(position.x / TILE_SIZE)),
        static_cast<int>(std::floor(-position.y / TILE_SIZE))
    };
}

glm::vec2 Tilemap::tileToWorld(const glm::ivec2& tile)
{
    return {
        tile.x * TILE_SIZE,
        -tile.y * TILE_SIZE
    };
}