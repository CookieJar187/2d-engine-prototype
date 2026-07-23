#pragma once

#include <glm/glm.hpp>

struct Transform2
{
    glm::vec2 position{0, 0};
    float rotation = 0;
    glm::vec2 scale{0, 0};
};