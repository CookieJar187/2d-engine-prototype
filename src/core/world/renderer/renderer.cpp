#include "renderer.hpp"

void Renderer::drawObjects(const glm::mat4 &view, const glm::mat4 &projection) const
{
    /*
    for (const auto &obj : world->objects)
    {
        obj->draw(view, projection);
    }
    */
    for (const auto &generation : world->objects)
    {
        for (const auto &object : generation)
        {
            object->draw(view, projection);
        }
    }
}