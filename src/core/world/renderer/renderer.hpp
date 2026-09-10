#pragma once

#include <glm/common.hpp>
#include "world.hpp"

class Renderer
{
private:
    World *world = nullptr;

public:
    Renderer(World &world) : world(&world) {};

    void drawObjects(const glm::mat4 &view, const glm::mat4 &projection) const;
};