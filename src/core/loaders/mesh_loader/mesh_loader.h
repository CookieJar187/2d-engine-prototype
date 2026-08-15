#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "mesh.h"

namespace MeshLoader
{
    Mesh loadQuad();
    Mesh load(const std::string &path);
}