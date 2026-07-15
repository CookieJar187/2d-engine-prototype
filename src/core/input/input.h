#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Input {
private:
    GLFWwindow* window;

public:
    Input(GLFWwindow* window);

    bool isKeyDown(int key) const;
    //bool isKeyPressed(int key) const;
};