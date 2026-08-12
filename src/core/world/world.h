#pragma once

#include <memory>
#include <vector>

#include "object.h"

class World
{
public:
    std::vector<std::unique_ptr<Object>> objects;
};