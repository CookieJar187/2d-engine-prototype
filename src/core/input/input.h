#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Input
{
private:
    GLFWwindow *window;

    bool currKeys[GLFW_KEY_LAST + 1]{};
    bool prevKeys[GLFW_KEY_LAST + 1]{};

    bool currMouse[GLFW_KEY_LAST + 1]{};
    bool prevMouse[GLFW_KEY_LAST + 1]{};

public:
    Input(GLFWwindow *window);

    void update();

    bool isKeyDown(int key) const;
    bool isKeyJustPressed(int key) const;
    bool isKeyJustReleased(int key) const;

    bool isMouseButtonDown(int mouseButton) const;
    bool isMouseButtonJustPressed(int mouseButton) const;
    bool isMouseButtonJustReleased(int mouseButton) const;

    glm::vec2 getMousePosition() const;
    glm::vec2 getScreenSize() const;
    glm::vec2 getMouseWorldPosition() const;
};