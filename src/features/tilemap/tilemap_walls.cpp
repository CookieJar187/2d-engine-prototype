#include "tilemap.h"

#include <iostream>

void Tilemap::createWall(const glm::vec2 pos, int type)
{
    Wall *wall;
    
    if (type == 1)
    {
        ObjectCreationData d{
            .name = "wall",
            .meshId = "sprite_mesh",
            .colliderId = "wall_collider",
            .materialId = "bricks_material"
        };

        //indestructableWalls.push_back(std::make_unique<Wall>(*this->scene, d));
        //wall = indestructableWalls.back().get();

        destructableWalls.push_back(std::make_unique<DestructableWall>(
            *this->scene,
            *this->damageRegistry,
            d,
            3750,
            *this->bricks,
            *this->bricksHit,
            *this->bricksDamaged,
            *this->bricksDestroyed
        ));
        wall = destructableWalls.back().get();
    }
    else if (type == 2)
    {
        ObjectCreationData d{
            .name = "boards_horizontal",
            .meshId = "sprite_mesh",
            .colliderId = "boards_horizontal_collider",
            .materialId = "boards_horizontal_material"
        };

        destructableWalls.push_back(std::make_unique<DestructableWall>(
            *this->scene,
            *this->damageRegistry,
            d,
            750,
            *this->boardsHorizontal,
            *this->boardsHorizontalHit,
            *this->boardsHorizontalDamaged,
            *this->boardsHorizontalDestroyed
        ));
        wall = destructableWalls.back().get();
    }
    else if (type == 3)
    {
        ObjectCreationData d{
            .name = "boards_vertical",
            .meshId = "sprite_mesh",
            .colliderId = "boards_vertical_collider",
            .materialId = "boards_vertical_material"
        };

        destructableWalls.push_back(std::make_unique<DestructableWall>(
            *this->scene,
            *this->damageRegistry,
            d,
            750,
            *this->boardsVertical,
            *this->boardsVerticalHit,
            *this->boardsVerticalDamaged,
            *this->boardsVerticalDestroyed
        ));
        wall = destructableWalls.back().get();
    }
    else if (type == 4)
    {
        ObjectCreationData d{
            .name = "tree",
            .meshId = "sprite_mesh",
            .colliderId = "tree_collider",
            .materialId = "tree_material"
        };

        destructableWalls.push_back(std::make_unique<DestructableWall>(
            *this->scene,
            *this->damageRegistry,
            d,
            500,
            *this->tree,
            *this->treeHit,
            *this->tree,
            *this->treeDestroyed
        ));
        wall = destructableWalls.back().get();
    }

    if (wall == nullptr)
        return;

    wall->obj->transform.position = pos;
}

void Tilemap::clearWalls()
{
    indestructableWalls.clear();
    destructableWalls.clear();
}