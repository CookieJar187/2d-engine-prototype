#include <glm/glm.hpp>
#include "vector2.h"

float Vector2::length() const
{
    glm::vec2 vec(x, y);
    return glm::length(vec);
}

Vector2 Vector2::normalize() const
{
    glm::vec2 vec(x, y);
    glm::vec2 norm =  glm::normalize(vec);
    return Vector2(norm.x, norm.y);
}