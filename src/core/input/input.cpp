#include "input.h"

Input::Input(GLFWwindow *window)
    : window(window) {}

void Input::update()
{
    // Keys
    std::copy(
        std::begin(currKeys),
        std::end(currKeys),
        std::begin(prevKeys)
    );

    for (int key = 0; key <= GLFW_KEY_LAST; ++key)
    {
        currKeys[key] = glfwGetKey(window, key) == GLFW_PRESS;
    }

    // Mouse
    std::copy(
        std::begin(currMouse),
        std::end(currMouse),
        std::begin(prevMouse)
    );

    for (int mouseButton = 0; mouseButton <= GLFW_MOUSE_BUTTON_LAST; ++mouseButton)
    {
        currMouse[mouseButton] = glfwGetMouseButton(window, mouseButton) == GLFW_PRESS;
    }
}

bool Input::isKeyDown(int key) const
{
    return currKeys[key];
}
bool Input::isKeyJustPressed(int key) const
{
    return currKeys[key] && !prevKeys[key];
}
bool Input::isKeyJustReleased(int key) const
{
    return !currKeys[key] && prevKeys[key];
}

bool Input::isMouseButtonDown(int mouseButton) const
{
    return currMouse[mouseButton];
}
bool Input::isMouseButtonJustPressed(int mouseButton) const
{
    return currMouse[mouseButton] && !prevMouse[mouseButton];
}
bool Input::isMouseButtonJustReleased(int mouseButton) const
{
    return !currMouse[mouseButton] && prevMouse[mouseButton];
}

glm::vec2 Input::getMousePosition() const
{
    double x = 0.0;
    double y = 0.0;

    glfwGetCursorPos(window, &x, &y);

    return glm::vec2(static_cast<float>(x), static_cast<float>(y));
}

glm::vec2 Input::getScreenSize() const
{
    int width = 0;
    int height = 0;

    glfwGetWindowSize(window, &width, &height);

    return glm::vec2(width, height);
}