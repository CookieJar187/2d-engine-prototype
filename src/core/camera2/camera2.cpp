#include "camera2.h"

glm::mat4 Camera2::getViewMatrix() const
{
    glm::mat4 view(1.0f);

    view = glm::rotate(
        view,
        -transform.rotation,
        glm::vec3(0.0f, 0.0f, 1.0f));

    view = glm::translate(
        view,
        glm::vec3(
            -transform.position.x,
            -transform.position.y,
            0.0f));

    return view;
}