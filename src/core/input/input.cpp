#include "input.h"

Input::Input(GLFWwindow *window)
    : window(window) {}

bool Input::isKeyDown(int key) const
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Input::isMouseButtonDown() const
{
    return glfwGetMouseButton(window, 0) == GLFW_PRESS;
}

glm::dvec2 Input::getMousePosition() const
{
    double x = 0.0;
    double y = 0.0;

    glfwGetCursorPos(window, &x, &y);

    return {x, y};
}