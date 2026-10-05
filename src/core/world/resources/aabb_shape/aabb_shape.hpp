#pragma once
#include <glm/glm.hpp>

struct AabbShape
{
    std::string name = "collider";

    glm::vec2 halfSize;

    AabbShape(
        glm::vec2 halfSize = glm::vec2(1, 1))
        : halfSize(halfSize) {};
};