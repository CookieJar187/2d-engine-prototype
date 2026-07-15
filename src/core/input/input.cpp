#include "input.h"

Input::Input(GLFWwindow* window)
    : window(window) {}

bool Input::isKeyDown(int key) const
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}