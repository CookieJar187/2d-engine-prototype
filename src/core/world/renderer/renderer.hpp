#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "world.hpp"

class Renderer
{
private:
    World *world = nullptr;

    glm::mat4 buildTransformMatrix(const Transform2 &transform) const;

    void drawObject(
        const Object &object,
        const glm::mat4 &view,
        const glm::mat4 &projection
    ) const;

public:
    Renderer(World &world) : world(&world) {};

    void render(const glm::mat4 &view, const glm::mat4 &projection) const;
};