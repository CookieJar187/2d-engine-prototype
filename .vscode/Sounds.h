#pragma once
#include "al.h"
#include "alc.h"

ALCdevice* soundDevice;
ALCcontext* soundContext;
void InitializeOpenAL() {
    soundDevice = alcOpenDevice(nullptr);

    if (!soundDevice)
    {
        std::cout << "Something went very insanely wrong" << std::endl;
    }

    soundContext = alcCreateContext(soundDevice, nullptr);

    if (!soundContext)
    {
        alcCloseDevice(soundDevice);
    }

    alcMakeContextCurrent(soundContext);
}

uint8_t loadedSoundSamples[44100];
struct PrivateSound {
    ALuint data, source;
} gunshot, explosion, wind,
tumbleweed;

void LoadSound(ALuint &buffer, const char* fsFile, int sampleCount) {
    std::ifstream file(fsFile, std::ios::binary);
    if (!file) {
        std::cout << "File not loaded" << std::endl;
        return;
    }
    file.seekg(44, std::ios::beg);
    file.read(reinterpret_cast<char*>(loadedSoundSamples), sampleCount);

    alGenBuffers(1, &buffer);
}
void CreateSound(PrivateSound &sound, int sampleCount) {
    alBufferData(
        sound.data,
        AL_FORMAT_MONO8,
        loadedSoundSamples,
        sampleCount,
        11025
    );
    alGenSources(1, &sound.source);
    alSourcei(sound.source, AL_BUFFER, sound.data);
}