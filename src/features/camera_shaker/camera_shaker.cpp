#include "camera_shaker.hpp"

float intensity = 0.0f;
bool shaking = false;

CameraShaker::CameraShaker(Camera2 &camera)
{
    this->camera = &camera;
}

void CameraShaker::update(float elapsed)
{
    if (intensity > 0.01)
    {
        if (shaking == false)
            shaking = true;

        this->camera->offset.position = {cos(elapsed * 53) * intensity, sin(elapsed * 62) * intensity};
        intensity *= 0.8;
    }
    else if (shaking)
    {
        shaking = false;
        this->camera->offset.position = {0, 0};
    }
}

void CameraShaker::explosionShake()
{
    if (intensity < EXPLOSION_SHAKE_FACTOR)
        intensity = EXPLOSION_SHAKE_FACTOR;
}

void CameraShaker::gunShake()
{
    if (intensity < GUN_SHAKE_FACTOR)
        intensity = GUN_SHAKE_FACTOR;
}