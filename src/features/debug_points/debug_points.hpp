#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "core.hpp"

struct DebugPoint
{
    Object *object = nullptr;
    float lifetime = 1.0f;
};

class DebugPoints
{
private:
    std::vector<DebugPoint> points;

    Scene *scene;
    ResourceManager *resourceManager;

public:
    DebugPoints(Core &core);

    void update(float deltaTime);

    void newPoint(glm::vec2 pos);

};