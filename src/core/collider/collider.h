#pragma once
#include <glm/glm.hpp>

struct AabbCollider {
    glm::vec2 halfSize;

    AabbCollider(
        glm::vec2 halfSize = glm::vec2(1, 1)
    )
    : halfSize(halfSize) {};
};