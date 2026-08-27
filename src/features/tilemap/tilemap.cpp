#include "tilemap.h"

#include <iostream>

Tilemap::Tilemap(
    Scene &scene,
    ResourceManager &resourceManager,
    DamageRegistry &damageRegistry)
{
    this->scene = &scene;
    this->damageRegistry = &damageRegistry;

    bricks = resourceManager.getMaterial("bricks_material");
    bricksHit = resourceManager.getMaterial("bricks_hit_material");
    bricksDamaged = resourceManager.getMaterial("bricks_damaged_material");
    bricksDestroyed = resourceManager.getMaterial("bricks_destroyed_material");

    boardsHorizontal = resourceManager.getMaterial("boards_horizontal_material");
    boardsHorizontalHit = resourceManager.getMaterial("boards_horizontal_hit_material");
    boardsHorizontalDamaged = resourceManager.getMaterial("boards_horizontal_damaged_material");
    boardsHorizontalDestroyed = resourceManager.getMaterial("boards_horizontal_destroyed_material");

    boardsVertical = resourceManager.getMaterial("boards_vertical_material");
    boardsVerticalHit = resourceManager.getMaterial("boards_vertical_hit_material");
    boardsVerticalDamaged = resourceManager.getMaterial("boards_vertical_damaged_material");
    boardsVerticalDestroyed = resourceManager.getMaterial("boards_vertical_destroyed_material");

    tree = resourceManager.getMaterial("tree_material");
    treeHit = resourceManager.getMaterial("tree_hit_material");
    treeDestroyed = resourceManager.getMaterial("tree_destroyed_material");
}

void Tilemap::update(float deltaTime)
{
    for (auto &v : destructableWalls)
    {
        v.get()->update(deltaTime);
    }
}

void Tilemap::load()
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            if (map[i][j] > 0)
                createWall(
                    {j * TILE_SIZE, -i * TILE_SIZE},
                    map[i][j]
                );
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