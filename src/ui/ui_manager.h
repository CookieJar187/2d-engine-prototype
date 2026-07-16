#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class UiManager
{
private:

public:
    int init(GLFWwindow* window);
    void buildUi();
    void drawUi();
    void destroyUi();
};