#include "renderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

glm::mat4 Renderer::buildTransformMatrix(const Transform2 &transform) const
{
    glm::mat4 matrix(1.0f);

    matrix = glm::translate(
        matrix,
        glm::vec3(
            transform.position.x,
            transform.position.y,
            0.0f));

    matrix = glm::rotate(
        matrix,
        transform.rotation,
        glm::vec3(0.0f, 0.0f, 1.0f));

    matrix = glm::scale(
        matrix,
        glm::vec3(
            transform.scale.x,
            transform.scale.y,
            1.0f));

    return matrix;
}

void Renderer::drawObject(
    const Object &object,
    const glm::mat4 &view,
    const glm::mat4 &projection
) const
{
    if (!object.mesh || !object.material)
        return;

    glUseProgram(object.material->shader->id);

    glm::mat4 model = buildTransformMatrix(object.transform);

    glUniformMatrix4fv(
        object.material->shader->modelLoc,
        1,
        GL_FALSE,
        &model[0][0]);

    glUniformMatrix4fv(
        object.material->shader->viewLoc,
        1,
        GL_FALSE,
        &view[0][0]);

    glUniformMatrix4fv(
        object.material->shader->projectionLoc,
        1,
        GL_FALSE,
        &projection[0][0]);

    // Select texture unit 0.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(
        GL_TEXTURE_2D,
        object.material->texture->id);
    glUniform1i(
        object.material->shader->textureLoc,
        0);

    glBindVertexArray(object.mesh->VAO);

    glDrawArrays(
        GL_TRIANGLES,
        0,
        object.mesh->vertexCount);
}

void Renderer::render(const glm::mat4 &view, const glm::mat4 &projection) const
{
    for (auto &generation : world->hierarchy)
    {
        for (auto &objectPtr : generation)
        {
            Object &object = *objectPtr;

            glm::mat4 localMatrix = buildTransformMatrix(object.transform);

            if (object.parent == nullptr)
                object.worldMatrix = localMatrix;
            else
                object.worldMatrix = object.parent->worldMatrix * localMatrix;

            drawObject(object, view, projection);
        }
    }
}