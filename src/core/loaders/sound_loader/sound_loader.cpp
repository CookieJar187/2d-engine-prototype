#include "sound_loader.hpp"

std::optional<Sound> SoundLoader::load(const char* path)
{
    Sound newSound;

    uint8_t loadedSoundSamples[44100];

    std::ifstream file(path, std::ios::binary);
    if (!file) {
        std::cout << "File not loaded" << std::endl;
        return std::nullopt;
    }
    file.seekg(44, std::ios::beg);
    file.read(reinterpret_cast<char*>(loadedSoundSamples), 44100);

    alGenBuffers(1, &newSound.data);

    //
    alBufferData(
        newSound.data,
        AL_FORMAT_MONO16,
        loadedSoundSamples,
        44100,
        44100
    );
    alGenSources(1, &newSound.source);
    alSourcei(newSound.source, AL_BUFFER, newSound.data);

    return newSound;
}