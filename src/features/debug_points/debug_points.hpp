#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "core.hpp"

class DebugPoints
{
private:
    struct DebugPoint
    {
        Object *object = nullptr;
        float lifetime = 0.5f;
    };

    std::vector<DebugPoint> points;

    Scene *scene;
    ResourceManager *resourceManager;

public:
    DebugPoints(Core &core);

    void update(float deltaTime);

    void newPoint(glm::vec2 pos);

};