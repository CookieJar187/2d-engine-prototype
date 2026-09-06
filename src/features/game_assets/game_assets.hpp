#pragma once

#include "core.hpp"

class GameAssets
{
public:
    GameAssets(Core &core);

private:
    ResourceManager *resourceManager;
};