#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "transform2.h"

struct Camera2 {
    Transform2 transform;

    glm::mat4 projection = glm::ortho(
        -400.0f, 400.0f,
        -300.0f, 300.0f,
        -1.0f, 1.0f
    );
};