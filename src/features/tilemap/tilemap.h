#pragma once

#define TILE_SIZE 100
#define MAP_HEIGHT 10
#define MAP_WIDTH 10

#include <vector>
#include <optional>
#include <memory>
#include <glm/common.hpp>

#include "scene.h"
#include "resource_manager.hpp"
#include "damage_registry.h"

#include "wall.hpp"
#include "destructable_wall.hpp"

class Tilemap
{
public:
    Tilemap(
        Scene &scene,
        ResourceManager &resourceManager,
        DamageRegistry &damageRegistry
    );

    void update(float deltaTime);

    void load();

    bool isWalkable(int x, int y);

    glm::ivec2 worldToTile(const glm::vec2& position);
    glm::vec2 tileToWorld(const glm::ivec2& tile);

    // Walls
    void createWall(const glm::vec2 pos, int type);
    void clearWalls();

private:
    std::vector<std::unique_ptr<Wall>> indestructableWalls;
    std::vector<std::unique_ptr<DestructableWall>> destructableWalls;

    Material *bricks;
    Material *bricksHit;
    Material *bricksDamaged;
    Material *bricksDestroyed;

    Material *boardsHorizontal;
    Material *boardsHorizontalHit;
    Material *boardsHorizontalDamaged;
    Material *boardsHorizontalDestroyed;

    Material *boardsVertical;
    Material *boardsVerticalHit;
    Material *boardsVerticalDamaged;
    Material *boardsVerticalDestroyed;

    Material *tree;
    Material *treeHit;
    Material *treeDestroyed;

    Scene *scene;
    DamageRegistry *damageRegistry;

    int map[MAP_HEIGHT][MAP_WIDTH] = {
        {0, 0, 4, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 4, 0, 0, 4},
        {4, 0, 1, 1, 2, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 3, 0, 0, 1, 2, 2, 1, 0},
        {4, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 4},
        {0, 0, 1, 1, 2, 1, 2, 2, 1, 0},
        {0, 0, 4, 0, 0, 0, 0, 0, 4, 0},
        {0, 4, 0, 0, 0, 4, 0, 0, 0, 0}
    };
};