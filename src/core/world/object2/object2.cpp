#include <iostream>

#include "object2.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Object2::getModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(
        model,
        glm::vec3(
            transform.position.x,
            transform.position.y,
            0.0f));

    model = glm::rotate(
        model,
        transform.rotation,
        glm::vec3(0.0f, 0.0f, 1.0f));

    model = glm::scale(
        model,
        glm::vec3(
            transform.scale.x,
            transform.scale.y,
            1.0f));

    return model;
}

void Object2::draw(const glm::mat4 &view, const glm::mat4 &projection) const
{

    if (!mesh || !material)
        return;

    glUseProgram(material->shader.id);

    glm::mat4 model = getModelMatrix();

    glUniformMatrix4fv(
        material->shader.modelLoc,
        1,
        GL_FALSE,
        &model[0][0]);

    glUniformMatrix4fv(
        material->shader.viewLoc,
        1,
        GL_FALSE,
        &view[0][0]);

    glUniformMatrix4fv(
        material->shader.projectionLoc,
        1,
        GL_FALSE,
        &projection[0][0]);

    glBindVertexArray(mesh->VAO);

    glDrawArrays(
        GL_TRIANGLES,
        0,
        mesh->vertexCount);
}