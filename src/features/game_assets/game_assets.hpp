#pragma once

#include "resource_manager.hpp"

class GameAssets
{
public:
    GameAssets(ResourceManager &resourceManager);

private:
    ResourceManager *resourceManager;
};