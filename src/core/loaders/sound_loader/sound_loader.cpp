#include "sound_loader.hpp"

#include <cstdint>
#include <cstring>
#include <vector>

template<typename T>
bool readValue(std::ifstream& file, T& value)
{
    return static_cast<bool>(file.read(reinterpret_cast<char*>(&value), sizeof(T)));
}

std::optional<Sound> SoundLoader::load(const char* path)
{
    std::ifstream file(path, std::ios::binary);

    if (!file)
    {
        std::cerr << "SoundLoader: failed to open `" << path << "`\n";
        return std::nullopt;
    }

    char riff[4];
    uint32_t riffSize;
    char wave[4];

    if (!file.read(riff, 4) || !readValue(file, riffSize) || !file.read(wave, 4))
    {
        std::cerr << "SoundLoader: invalid WAV header\n";
        return std::nullopt;
    }

    if (std::memcmp(riff, "RIFF", 4) != 0 || std::memcmp(wave, "WAVE", 4) != 0)
    {
        std::cerr << "SoundLoader: file is not a WAV file\n";
        return std::nullopt;
    }

    uint16_t audioFormat = 0;
    uint16_t channels = 0;
    uint32_t sampleRate = 0;
    uint16_t bitsPerSample = 0;

    std::vector<uint8_t> audioData;

    bool foundFormat = false;
    bool foundData = false;

    while (file && (!foundFormat || !foundData))
    {
        char chunkId[4];
        uint32_t chunkSize;

        if (!file.read(chunkId, 4))
            break;

        if (!readValue(file, chunkSize))
            break;

        if (std::memcmp(chunkId, "fmt ", 4) == 0)
        {
            uint32_t byteRate;
            uint16_t blockAlign;

            if (!readValue(file, audioFormat) ||
                !readValue(file, channels) ||
                !readValue(file, sampleRate) ||
                !readValue(file, byteRate) ||
                !readValue(file, blockAlign) ||
                !readValue(file, bitsPerSample))
            {
                std::cerr << "SoundLoader: invalid fmt chunk\n";
                return std::nullopt;
            }

            // Standard PCM fmt 16 byte data
            if (chunkSize > 16)
            {
                file.seekg(chunkSize - 16, std::ios::cur);
            }

            foundFormat = true;
        }
        else if (std::memcmp(chunkId, "data", 4) == 0)
        {
            audioData.resize(chunkSize);

            if (!file.read(reinterpret_cast<char*>(audioData.data()), chunkSize))
            {
                std::cerr << "SoundLoader: failed reading audio data\n";
                return std::nullopt;
            }

            foundData = true;
        }
        else
            file.seekg(chunkSize, std::ios::cur);

        if (chunkSize % 2 != 0)
            file.seekg(1, std::ios::cur);
    }

    if (!foundFormat || !foundData)
    {
        std::cerr << "SoundLoader: missing fmt or data chunk\n";
        return std::nullopt;
    }

    // 1 = uncompressed PCM
    if (audioFormat != 1)
    {
        std::cerr << "SoundLoader: unsupported WAV format: " << audioFormat << std::endl;
        return std::nullopt;
    }

    ALenum format;

    if (channels == 1 && bitsPerSample == 8)
        format = AL_FORMAT_MONO8;

    else if (channels == 1 && bitsPerSample == 16)
        format = AL_FORMAT_MONO16;

    else if (channels == 2 && bitsPerSample == 8)
        format = AL_FORMAT_STEREO8;

    else if (channels == 2 && bitsPerSample == 16)
        format = AL_FORMAT_STEREO16;

    else
    {
        std::cerr << "SoundLoader: unsupported WAV format: " << channels << " channels, " << bitsPerSample << " bits\n";
        return std::nullopt;
    }

    Sound newSound;

    alGenBuffers(1, &newSound.data);

    alBufferData(
        newSound.data,
        format,
        audioData.data(),
        static_cast<ALsizei>(audioData.size()),
        static_cast<ALsizei>(sampleRate)
    );

    alGenSources(1, &newSound.source);

    alSourcei(
        newSound.source,
        AL_BUFFER,
        newSound.data
    );

    return newSound;
}