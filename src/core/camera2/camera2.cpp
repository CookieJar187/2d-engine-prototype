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

glm::vec2 Camera2::screenToWorld(
    const glm::vec2& screenPosition,
    const glm::ivec2& viewportSize
) const
{
    float normalizedX = (2.0f * screenPosition.x) / static_cast<float>(viewportSize.x) - 1.0f;
    float normalizedY = 1.0f - (2.0f * screenPosition.y) / static_cast<float>(viewportSize.y);

    glm::vec4 clipPosition(
        normalizedX,
        normalizedY,
        0.0f,
        1.0f
    );

    glm::mat4 inverseViewProjection = glm::inverse(this->projection * this->getViewMatrix());
    glm::vec4 worldPosition = inverseViewProjection * clipPosition;

    if (worldPosition.w != 0.0f)
        worldPosition /= worldPosition.w;

    return glm::vec2(
        worldPosition.x,
        worldPosition.y
    );
}