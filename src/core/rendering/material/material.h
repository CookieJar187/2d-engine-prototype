#pragma once

#include <glm/glm.hpp>
#include "shader.h"
#include "texture.h"

struct Material
{
    Shader *shader;
    Texture *texture;
};