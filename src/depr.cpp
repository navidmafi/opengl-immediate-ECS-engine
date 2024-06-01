
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <fmt/core.h>
#include <time.h>
#include <vector>
#include <unistd.h>
#include "utils.h"
#include <list>

const int TPS = 20;

struct AngleAnimationConfig
{
    double angle;

    int movementPerTick;
};

struct V3DAnimation
{
    AngleAnimationConfig x;
    AngleAnimationConfig y;
    AngleAnimationConfig z;
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {}
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {}
void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {}
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {}
void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void set_window_scale_callback(GLFWwindow *window, float xscale, float yscale) {}

void initGLFWCallbacks(GLFWwindow *window)
{
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetErrorCallback(error_callback);
    glfwSetWindowContentScaleCallback(window, set_window_scale_callback);
}

V3DAnimation animations[UINT8_MAX];

void glRotate(double x, double y, double z)
{
    glRotatef(x, 1, 0, 0);
    glRotatef(y, 0, 1, 0);
    glRotatef(z, 0, 0, 1);
}

void Cube(double size, double rX, double rY, double rZ)
{
    glRotate(rX, rY, rZ);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(size, 0.0, 0.0);
    glVertex3f(size, size, 0.0);
    glVertex3f(0.0, size, 0.0);
    glVertex3f(0.0, 0.0, -size);
    glVertex3f(size, 0.0, -size);
    glVertex3f(size, size, -size);
    glVertex3f(0.0, size, -size);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(0.0, size, 0.0);
    glVertex3f(0.0, size, -size);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, -size);
    glVertex3f(size, 0.0, 0.0);
    glVertex3f(size, 0.0, -size);
    glVertex3f(size, size, 0.0);
    glVertex3f(size, size, -size);
    glEnd();
}

void updateByDeltaTime(double *value, int deltaTimeMS, double speed)
{

    fmt::println("{} {} {}", *value, deltaTimeMS, speed);
    *value += (((deltaTimeMS / 1000) * TPS) * speed);
}

void animationTick(int objectIdx, int deltaTimeMS)
{
    V3DAnimation animation = animations[objectIdx];

    updateByDeltaTime(&animation.x.angle, deltaTimeMS, animation.x.movementPerTick);
    // updateByDeltaTime((double *)*animation.y.angle, deltaTimeMS, (double)animation.y.movementPerTick);
    // updateByDeltaTime((double *)*animation.z.angle, deltaTimeMS, (double)animation.z.movementPerTick);
}

void OnStart()
{
    animations[0] = V3DAnimation{
        .x = AngleAnimationConfig{
            .angle = 20.0,
            .movementPerTick = 40}};
};

void OnUpdate(int dtMS)
{

    fmt::println(std::to_string(dtMS).c_str());

    animationTick(1, dtMS);
}

static int prevms = (int)time(NULL);
void Display()
{

    // prvMs = curMs;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Cube(0.5, animations[0].x.angle, 20, 0);

    usleep(100 * 1000);
}

/*
    draw
    input
    audio
*/
