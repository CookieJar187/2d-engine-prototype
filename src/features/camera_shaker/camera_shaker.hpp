#pragma once

#define GUN_SHAKE_FACTOR 5
#define EXPLOSION_SHAKE_FACTOR 50
#define DAMAGE_SHAKE_FACTOR 40

#include <iostream>

#include "camera.h"

class CameraShaker
{
private:
    Camera2 *camera;

public:
    CameraShaker(Camera2 &camera);

    void update(float elapsed);

    void explosionShake();
    void gunShake();

};