#include "tilemap.h"

#include <iostream>

Tilemap::Tilemap(
    Core &core,
    DamageRegistry &damageRegistry)
{
    this->scene = &core.scene;
    this->damageRegistry = &damageRegistry;

    bricks = core.resourceManager.getMaterial("bricks_material");
    bricksHit = core.resourceManager.getMaterial("bricks_hit_material");
    bricksDamaged = core.resourceManager.getMaterial("bricks_damaged_material");
    bricksDestroyed = core.resourceManager.getMaterial("bricks_destroyed_material");

    boardsHorizontal = core.resourceManager.getMaterial("boards_horizontal_material");
    boardsHorizontalHit = core.resourceManager.getMaterial("boards_horizontal_hit_material");
    boardsHorizontalDamaged = core.resourceManager.getMaterial("boards_horizontal_damaged_material");
    boardsHorizontalDestroyed = core.resourceManager.getMaterial("boards_horizontal_destroyed_material");

    boardsVertical = core.resourceManager.getMaterial("boards_vertical_material");
    boardsVerticalHit = core.resourceManager.getMaterial("boards_vertical_hit_material");
    boardsVerticalDamaged = core.resourceManager.getMaterial("boards_vertical_damaged_material");
    boardsVerticalDestroyed = core.resourceManager.getMaterial("boards_vertical_destroyed_material");

    tree = core.resourceManager.getMaterial("tree_material");
    treeHit = core.resourceManager.getMaterial("tree_hit_material");
    treeDestroyed = core.resourceManager.getMaterial("tree_destroyed_material");
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