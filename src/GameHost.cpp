#include <GameHost.hpp>
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
    glfwSetFramebufferSizeCallback(window, internal_framebufferSizeCallback);
}

GLFWwindow *GameHost::getWindow() const
{
    return window;
}

// void GameHost::onResize = default;

void GameHost::onResize(std::function<void(int, int)> callback)
{
    resizeCallback = callback;
}

void GameHost::triggerResize(int newWidth, int newHeight)
{
    if (resizeCallback)
    {
        resizeCallback(newWidth, newHeight);
    }
}

void GameHost::internal_framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    GameHost *host = static_cast<GameHost *>(glfwGetWindowUserPointer(window));
    if (host)
    {
        host->triggerResize(width, height);
    }
}