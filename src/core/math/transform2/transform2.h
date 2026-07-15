#pragma once

#include <glm/glm.hpp>

struct Transform2 {
    glm::vec2 position;
    float rotation = 0;
    glm::vec2 scale;
};