#pragma once

#include <vector>
#include <glm/vec2.hpp>

#include "tilemap.h"

namespace pathfinding
{
    std::vector<glm::ivec2> getPathTo(glm::ivec2 start, glm::ivec2 target, Tilemap &tilemap);
}