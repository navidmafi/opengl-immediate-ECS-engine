#include "GameHost.hpp"

GameHost::GameHost(WindowConfig wc) : window_config(wc), window(nullptr) {}

void GameHost::hostWindowInit()
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_RESIZABLE, window_config.resizable);
    glfwWindowHint(GLFW_DECORATED, window_config.window_borders);

    window = glfwCreateWindow(640, 480, window_config.window_title, NULL, NULL);

    if (!window)
    {
        throw std::runtime_error("Failed to create window");
    }

    glfwMakeContextCurrent(window);
}

GLFWwindow *GameHost::getWindow() const
{
    return window;
}
