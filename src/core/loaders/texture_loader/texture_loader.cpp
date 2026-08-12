#include "texture_loader.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <filesystem>
#include <iostream>

Texture TextureLoader::load(const std::string &path)
{
    Texture texture;

    stbi_set_flip_vertically_on_load(true);

    unsigned char *pixels = stbi_load(
        path.c_str(),
        &texture.width,
        &texture.height,
        &texture.channels,
        0);

    if (pixels == nullptr)
        throw std::runtime_error("Failed to load texture: " + path + "\nReason: " + stbi_failure_reason());

    GLenum sourceFormat;

    if (texture.channels == 4)
        sourceFormat = GL_RGBA;
    else if (texture.channels == 3)
        sourceFormat = GL_RGB;
    else
    {
        stbi_image_free(pixels);

        throw std::runtime_error("Unsupported channel count in texture: " + path);
    }

    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        sourceFormat,
        texture.width,
        texture.height,
        0,
        sourceFormat,
        GL_UNSIGNED_BYTE,
        pixels);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(pixels);

    return texture;
}

void TextureLoader::destroy(Texture &texture)
{
    if (texture.id == 0)
        return;

    glDeleteTextures(1, &texture.id);

    texture.id = 0;
    texture.width = 0;
    texture.height = 0;
    texture.channels = 0;
}