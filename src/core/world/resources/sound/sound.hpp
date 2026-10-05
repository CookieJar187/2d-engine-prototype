#pragma once

#include <al.h>
#include <alc.h>

struct Sound
{
    ALuint data, source;

    void play()
    {
        alSourcePlay(this->source);
    }

    void stop()
    {
        alSourceStop(this->source);
    }
};