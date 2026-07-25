#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Input
{
private:
    GLFWwindow *window;

public:
    Input(GLFWwindow *window);

    bool isKeyDown(int key) const;
    bool isMouseButtonDown() const;

    glm::dvec2 getMousePosition() const;
};