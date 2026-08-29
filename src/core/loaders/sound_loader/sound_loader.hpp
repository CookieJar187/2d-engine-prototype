#pragma once

#include <iostream>
#include <fstream>
#include <optional>

#include <al.h>
#include <alc.h>

#include "sound.hpp"

namespace SoundLoader
{
    std::optional<Sound> load(const char* path);
}