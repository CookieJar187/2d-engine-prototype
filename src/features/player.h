#pragma once

#include "input.h"
#include "object2.h"
#include "scene.h"

class Player {
private:
    Object2* body = nullptr;
    Input* input = nullptr;
    Scene* scene = nullptr;

    int maxSpeed = 200;

public:
    void init(Scene& scene, Input& input);
    void update(float deltaTime);
};