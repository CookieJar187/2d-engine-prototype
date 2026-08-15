#include "mesh_loader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

Mesh MeshLoader::loadQuad()
{
    Mesh m;

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f};

    glGenVertexArrays(1, &m.VAO);
    glGenBuffers(1, &m.VBO);

    glBindVertexArray(m.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m.VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof(float),
        (void *)0);

    glEnableVertexAttribArray(0);

    // UV
    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof(float),
        reinterpret_cast<void *>(3 * sizeof(float)));

    glEnableVertexAttribArray(1);

    m.vertexCount = 6;

    return m;
}

Mesh MeshLoader::load(const std::string& path)
{
    Mesh mesh;

    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr << "Failed to open OBJ: " << path << '\n';
        return mesh;
    }

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uvs;

    std::vector<float> vertices;

    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream stream(line);

        std::string type;
        stream >> type;

        if (type == "v")
        {
            glm::vec3 position;

            stream >> position.x >> position.y >> position.z;

            positions.push_back(position);
        }

        else if (type == "vt")
        {
            glm::vec2 uv;

            stream >> uv.x >> uv.y;

            uvs.push_back(uv);
        }

        else if (type == "f")
        {
            std::string vertexData;

            while (stream >> vertexData)
            {
                std::stringstream vertexStream(vertexData);

                std::string positionIndexString;
                std::string uvIndexString;

                std::getline(vertexStream, positionIndexString, '/');
                std::getline(vertexStream, uvIndexString, '/');

                int positionIndex = std::stoi(positionIndexString) - 1;
                int uvIndex = std::stoi(uvIndexString) - 1;

                glm::vec3 position = positions[positionIndex];
                glm::vec2 uv = uvs[uvIndex];

                vertices.push_back(position.x);
                vertices.push_back(position.y);
                vertices.push_back(position.z);

                vertices.push_back(uv.x);
                vertices.push_back(uv.y);
            }
        }
    }

    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);

    glBindVertexArray(mesh.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
        GL_STATIC_DRAW
    );

    // Position
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof(float),
        reinterpret_cast<void*>(0)
    );

    glEnableVertexAttribArray(0);

    // UV
    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof(float),
        reinterpret_cast<void*>(3 * sizeof(float))
    );

    glEnableVertexAttribArray(1);

    mesh.vertexCount = vertices.size() / 5;

    return mesh;
}