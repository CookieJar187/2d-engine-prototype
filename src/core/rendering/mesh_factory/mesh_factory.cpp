#include <mesh_factory.h>

Mesh MeshFactory::createTriangle() {
    Mesh m;

    float vertices[] = {
         0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    glGenVertexArrays(1, &m.VAO);
    glGenBuffers(1, &m.VBO);

    glBindVertexArray(m.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,                //Index of the vertex attribute
        3,                //Number of components per vertex attribute
        GL_FLOAT,         //Data type of each component
        GL_FALSE,         //Whether fixed-point data should be normalized
        3*sizeof(float),  //Byte offset between consecutive vertex attributes
        (void*)0
    );

    glEnableVertexAttribArray(0);

    m.vertexCount = 3;

    return m;
}

Mesh MeshFactory::createSquare() {
    Mesh m;

    float vertices[] = {
         0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,

         0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    glGenVertexArrays(1, &m.VAO);
    glGenBuffers(1, &m.VBO);

    glBindVertexArray(m.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    m.vertexCount = 6;

    return m;
}