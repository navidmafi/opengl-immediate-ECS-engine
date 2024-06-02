#ifndef GAMEHOST_H
#define GAMEHOST_H

#include <stdexcept>
#include <WindowConfig.hpp>
#include <Renderer.hpp>
#include <Renderer.hpp>
#include <functional>

// C++ 11 : jalebe

/*


It has a similar syntax, except you remove the identifier from the pointer:
z
using FunctionPtr = void (*)();

*/
using TRendererCallback = void (OpenGLRenderer::*)(int, int);
// using TGLFWFBChangeCallback = void (*)(GLFWwindow *, int, int);
class GameHost
{
private:
    WindowConfig window_config;
    GLFWwindow *window;
    std::function<void(int, int)> resizeCallback;
    static void internal_framebufferSizeCallback(GLFWwindow *window, int width, int height);

public:
    GameHost(WindowConfig wc);
    void hostWindowInit();
    GLFWwindow *getWindow() const;
    void onResize(std::function<void(int, int)> callback);
    void triggerResize(int newWidth, int newHeight);
};

#endif // GAMEHOST_H
