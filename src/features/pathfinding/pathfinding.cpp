#include "pathfinding.hpp"

#include <iostream>
#include <memory>
#include <queue>

struct Node
{
    glm::ivec2 coordinates;
    Node *parent;
};

std::vector<glm::ivec2> getBackToStart(
    std::vector<std::unique_ptr<Node>> &nodes
)
{
    std::vector<glm::ivec2> breadcrums;

    Node *child = nodes.back().get();
    while (true)
    {
        child = child->parent;
        
        if (child != nullptr)
            breadcrums.push_back(child->coordinates);
        else
            break;
    }

    std::reverse(breadcrums.begin(), breadcrums.end());
    return breadcrums;
}

std::vector<glm::ivec2> pathfinding::getPathTo(glm::ivec2 start, glm::ivec2 target, Tilemap &tilemap)
{
    std::vector<std::unique_ptr<Node>> nodes;
    std::queue<Node *> toSearch;
    bool searched[MAP_WIDTH][MAP_HEIGHT] = {};

    nodes.push_back(std::make_unique<Node>(start, nullptr));
    searched[start.x][start.y] = true;

    Node *startNode = nodes[0].get();
    toSearch.push(startNode);

    while (toSearch.size() > 0)
    {
        for (int i = 0; i < toSearch.size(); i++)
        {
            Node *currNode = toSearch.front();
            glm::ivec2 currCoord = currNode->coordinates;

            searched[currCoord.x][currCoord.y] = true;

            glm::ivec2 north{currCoord.x, currCoord.y + 1};
            glm::ivec2 south{currCoord.x, currCoord.y - 1};
            glm::ivec2 east{currCoord.x + 1, currCoord.y};
            glm::ivec2 west{currCoord.x - 1, currCoord.y};
            
            if (
                north.y < MAP_HEIGHT &&
                !searched[north.x][north.y] &&
                tilemap.isWalkable(north.x, north.y)
            )
            {
                nodes.push_back(std::make_unique<Node>(north, currNode));
                searched[north.x][north.y] = true;
                toSearch.push(nodes.back().get());

                if (north == target)
                    return getBackToStart(nodes);
            }

            if (
                south.y >= 0 &&
                !searched[south.x][south.y] &&
                tilemap.isWalkable(south.x, south.y)
            )
            {
                nodes.push_back(std::make_unique<Node>(south, currNode));
                searched[south.x][south.y] = true;
                toSearch.push(nodes.back().get());

                if (south == target)
                    return getBackToStart(nodes);
            }

            if (
                east.x < MAP_WIDTH &&
                !searched[east.x][east.y] &&
                tilemap.isWalkable(east.x, east.y)
            )
            {
                nodes.push_back(std::make_unique<Node>(east, currNode));
                searched[east.x][east.y] = true;
                toSearch.push(nodes.back().get());

                if (east == target)
                    return getBackToStart(nodes);
            }

            if (
                west.x >= 0 &&
                !searched[west.x][west.y] &&
                tilemap.isWalkable(west.x, west.y)
            )
            {
                nodes.push_back(std::make_unique<Node>(west, currNode));
                searched[west.x][west.y] = true;
                toSearch.push(nodes.back().get());

                if (west == target)
                    return getBackToStart(nodes);
            }

            toSearch.pop();
        }
    }

    return {};
}