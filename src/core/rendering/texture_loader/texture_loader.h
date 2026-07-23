#pragma once

#include <string>

#include "texture.h"

namespace TextureLoader
{
    Texture load(const std::string &path);
    void destroy(Texture &texture);
};