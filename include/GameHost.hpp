#ifndef GAMEHOST_H
#define GAMEHOST_H

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <WindowConfig.hpp>

class GameHost
{
private:
    WindowConfig window_config;
    GLFWwindow *window;

public:
    GameHost(WindowConfig wc);
    void hostWindowInit();
    GLFWwindow *getWindow() const;
};

#endif // GAMEHOST_H
