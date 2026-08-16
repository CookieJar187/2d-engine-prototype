#include "tilemap.h"

#include <algorithm>
#include <vector>

struct Node
{
    glm::ivec2 value;

    int g = 0;
    int h = 0;

    glm::ivec2 parent{-1, -1};

    int f() const
    {
        return g + h;
    }
};

std::vector<glm::ivec2> Tilemap::pathfind(
    const glm::vec2 startPos,
    const glm::vec2 endPos)
{
    std::vector<glm::ivec2> path;

    glm::ivec2 start = getTileFromPosition(startPos);
    glm::ivec2 end   = getTileFromPosition(endPos);

    Node startNode;
    startNode.value = start;
    startNode.g = 0;
    startNode.h = std::abs(start.x - end.x) + std::abs(start.y - end.y);

    std::vector<Node> toSearch{startNode};
    std::vector<Node> processed;

    while (!toSearch.empty())
    {
        auto currentIt = toSearch.begin();

        for (auto it = toSearch.begin(); it != toSearch.end(); ++it)
        {
            if (it->f() < currentIt->f() || (it->f() == currentIt->f() && it->h < currentIt->h))
                currentIt = it;
        }

        Node current = *currentIt;

        toSearch.erase(currentIt);
        processed.push_back(current);

        if (current.value == end)
        {
            glm::ivec2 tile = current.value;

            while (tile != start)
            {
                path.push_back(getPositionFromTile(tile));

                auto nodeIt = std::find_if(
                    processed.begin(),
                    processed.end(),
                    [&](const Node& node)
                    {
                        return node.value == tile;
                    }
                );

                if (nodeIt == processed.end())
                    break;

                tile = nodeIt->parent;
            }

            path.push_back(getPositionFromTile(start));

            std::reverse(path.begin(), path.end());

            return path;
        }

        const glm::ivec2 directions[] =
        {
            { 1,  0},
            {-1,  0},
            { 0,  1},
            { 0, -1}
        };

        for (const auto& direction : directions)
        {
            glm::ivec2 neighbourPos =
                current.value + direction;

            int x = neighbourPos.x;
            int y = neighbourPos.y;

            if (x < 0 || y < 0 ||
                x >= MAP_WIDTH ||
                y >= MAP_HEIGHT)
            {
                continue;
            }

            if (map[x][y] != 0)
                continue;

            bool wasProcessed = std::any_of(
                processed.begin(),
                processed.end(),
                [&](const Node& node)
                {
                    return node.value == neighbourPos;
                }
            );

            if (wasProcessed)
                continue;

            int newG = current.g + 1;

            auto neighbourIt = std::find_if(
                toSearch.begin(),
                toSearch.end(),
                [&](const Node& node)
                {
                    return node.value == neighbourPos;
                }
            );

            if (neighbourIt == toSearch.end())
            {
                Node neighbour;

                neighbour.value = neighbourPos;
                neighbour.g = newG;
                neighbour.h = std::abs(neighbourPos.x - end.x) + std::abs(neighbourPos.y - end.y);

                neighbour.parent = current.value;

                toSearch.push_back(neighbour);
            }
            else if (newG < neighbourIt->g)
            {
                neighbourIt->g = newG;
                neighbourIt->parent = current.value;
            }
        }
    }

    return {};
}