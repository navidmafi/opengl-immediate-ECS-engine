#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <fmt/core.h>
#include <time.h>
#include <vector>
#include <unistd.h>
#include "utils.h"
#include <list>

struct RGBAC
{
    float r, g, b, a;
};

template <typename Vec3Type>
struct Vec3
{
    Vec3Type x;
    Vec3Type y;
    Vec3Type z;
};

template <typename Vec2Type>
struct Vec2
{
    Vec2Type x;
    Vec2Type y;
};

using Position = Vec3<int>;
using Rotation = Vec3<int>;
using Scale = Vec3<float>;

using WireMesh = std::vector<Position>; // A wireframe mesh consisting of only vertices. persumed to be rendered using GL_LINES

struct WindowConfig
{
    char window_title[128];
    bool window_borders;
    bool resizable;
};

struct RendererConfig
{
    int fb_width;
    int fb_height;

    bool vsync;
    int framecap;
    bool compat_profile;
};

struct Face
{
    std::vector<Position> vertices;
    RGBAC color;
};

class GameHost
{

private:
    WindowConfig window_config;
    GLFWwindow *window;

public:
    GameHost(WindowConfig wc)
    {
        this->window_config = wc;
    }

    GLFWwindow *getWindow()
    {
        return this->window;
    }
    void hostWindowInit()
    {
        GLFWwindow *window;

        if (!glfwInit())
        {
            throw std::runtime_error("failed to init GLFW");
        }

        // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

        glfwWindowHint(GLFW_RESIZABLE, this->window_config.resizable);
        glfwWindowHint(GLFW_DECORATED, this->window_config.window_borders);

        window = glfwCreateWindow(640, 480, this->window_config.window_title, NULL, NULL);

        glfwMakeContextCurrent(window);

        if (!window)
        {
            throw std::runtime_error("failed to init window");
        }

        this->window = window;
    }
};

class GameObject
{
public:
    Position position;
    Rotation rotation;
    Scale scale;
    RGBAC color;

    std::vector<Face> faces;

    virtual void render() = 0;
    virtual void update(float deltaTime) = 0;
    GameObject() : position{0, 0, 0}, rotation{0, 0, 0}, scale{1.0f, 1.0f, 1.0f}, color{1.0f, 1.0f, 1.0f, 1.0f} {}
};

class Scene
{
private:
    std::list<GameObject *> objects;

public:
    RGBAC background = RGBAC{0, 0, 0, 1};

    void addObj(GameObject *obj)
    {
        (this->objects).push_back(obj);
    }

    void renderScene()
    {

        std::list<GameObject *>::iterator obj;
        for (obj = objects.begin(); obj != objects.end(); ++obj)
        {
            (*obj)->render();
        }
    }
};

class OpenGLRenderer
{
private:
    RendererConfig config;
    const char *vendor_name;
    const char *renderer_name;
    const char *gl_version;

    void get_env()
    {

        this->vendor_name = reinterpret_cast<const char *>(glGetString(GL_VENDOR));

        this->renderer_name = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

        this->gl_version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
    }

public:
    OpenGLRenderer(RendererConfig config)
    {
        this->config = config;
    }

    void initializeCtx()
    {
        int version = gladLoadGL(glfwGetProcAddress);
        if (version == 0)
        {
            throw std::runtime_error("Failed to initialize OpenGL context");
        }
        this->get_env();

        fmt::println("OpenGL {} on {}", this->gl_version, this->renderer_name);
    }

    void initializeGL()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glShadeModel(GL_SMOOTH);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    }
};

class Cube : public GameObject
{
public:
    Cube()
    {
        faces = {
            {{{-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1}}, {1.0f, 0.0f, 0.0f, 1.0f}}, // back face, red
            {{{-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}}, {0.0f, 1.0f, 0.0f, 1.0f}},     // front face, green
            {{{-1, -1, -1}, {-1, 1, -1}, {-1, 1, 1}, {-1, -1, 1}}, {0.0f, 0.0f, 1.0f, 1.0f}}, // left face, blue
            {{{1, -1, -1}, {1, 1, -1}, {1, 1, 1}, {1, -1, 1}}, {1.0f, 1.0f, 0.0f, 1.0f}},     // right face, yellow
            {{{-1, -1, -1}, {1, -1, -1}, {1, -1, 1}, {-1, -1, 1}}, {1.0f, 0.0f, 1.0f, 1.0f}}, // bottom face, magenta
            {{{-1, 1, -1}, {1, 1, -1}, {1, 1, 1}, {-1, 1, 1}}, {0.0f, 1.0f, 1.0f, 1.0f}}      // top face, cyan
        };
    }

    void update(float deltaTime) override
    {
        rotation.y += 90.0f * deltaTime;
    }

    void render() override
    {

        glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
        glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
        glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
        glScalef(scale.x, scale.y, scale.z);

        glBegin(GL_QUADS); // Change to GL_QUADS to draw each face

        for (const auto &face : faces)
        {
            glColor4f(face.color.r, face.color.g, face.color.b, face.color.a); // Set face color
            for (const auto &vertex : face.vertices)
            {
                glVertex3i(vertex.x, vertex.y, vertex.z); // Draw vertex
            }
        }

        glEnd();
        glPopMatrix();
    }
};

// class AnimationManager {

// }

int main()
{
    WindowConfig window_config = {
        .window_title = "glfw",
        .window_borders = false,
        .resizable = true,
    };
    RendererConfig renderer_config = {
        .fb_width = 600,
        .fb_height = 600,
        .vsync = false,
        .framecap = 30,
        .compat_profile = true};

    GameHost host(window_config);
    OpenGLRenderer renderer(renderer_config);
    Scene scene;

    try
    {
        host.hostWindowInit();
        renderer.initializeCtx();
        renderer.initializeGL();

        Cube cube;
        cube.rotation = Rotation{50, 10, 20};
        cube.scale = Scale{0.5, 0.5, 0.5};
        scene.addObj(&cube);

        while (!glfwWindowShouldClose(host.getWindow()))
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();
            scene.renderScene();
            glfwSwapBuffers(host.getWindow());
            glfwPollEvents();
        }
    }
    catch (const std::exception &e)
    {
        fmt::print("Exception: {}\n", e.what());
        return -1;
    }

    glfwDestroyWindow(host.getWindow());
    glfwTerminate();
    fmt::println("Exiting cleanly");

    return 0;
}

// enum EventType {
//     fbsizechange,
//     getkey
// };

// class EventContainer {

//     private:
//          using eventHandler = void (*);
//          eventHandler handlers[10]; // max of 10 handlers

// }

// class WindowEventsManager {

//     private:
//      GLFWwindow* window;

//      ResizeEventsContainer =

//     public:
//         WindowEventsManager(GLFWwindow* wnd) {
//             this -> window = wnd;
//         }

//         addEventHandler(EventType evtype, void (*func)()) {
//                 if (evtype == EventType::fbsizechange) {

//                 }
//         }
// };

class TAKKAEngine
{

private:
    static const int TPS = 20;

    static int uptimeMS;

    static int lastTickMS;

    static void initWindow(char *argc)
    {
    }

    static void fb_size_cb(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
};

/*       ----------------           */

// int main(void)
// {

//     GLFWwindow *window = initWindow();

//     initGL();

//     double previousTime = glfwGetTime();
//     double currentTime;
//     double deltaTime;

//     while (!glfwWindowShouldClose(window))
//     {

//         currentTime = glfwGetTime();
//         deltaTime = currentTime - previousTime;
//         previousTime = currentTime;

//         OnUpdate(static_cast<int>(deltaTime * 1000));

//         glLoadIdentity();

//         Display();
//         glfwSwapBuffers(window);

//         glFinish();
//         glfwPollEvents();
//     }
//     glfwDestroyWindow(window);
//     glfwTerminate();
// }

// int main(void) {

//     glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

//     GLuint VertexArrayID;
//     glGenVertexArrays(1, &VertexArrayID);
//     glBindVertexArray(VertexArrayID);

//     GLuint programID = LoadShaders("shaders/triangle.vert", "shaders/triangle.frag");

//     static const GLfloat g_vertex_buffer_data[] = {
//         -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//     };

//     GLuint vertexbuffer;
//     glGenBuffers(1, &vertexbuffer);
//     glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

//     while (!glfwWindowShouldClose(window))
//     {
//         // fmt::println("[render]");

//         /* Render here */
//         // fmt::println("[render] clearing buffers");
//         glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//         glUseProgram(programID);

//         glEnableVertexAttribArray(0);
//         glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//         glVertexAttribPointer(0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
//                               3, // size
//                               GL_FLOAT, // type
//                               GL_FALSE, // normalized?
//                               0,        // stride
//                               (void *)0 // array buffer offset
//         );

//         glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
//         glDisableVertexAttribArray(0);

//         glfwSwapBuffers(window);

//         /* Poll for and process events */
//         glfwPollEvents();
//     }

//     glDeleteBuffers(1, &vertexbuffer);
//     glDeleteVertexArrays(1, &VertexArrayID);
//     glDeleteProgram(programID);

//     glfwTerminate();
//     return 0;
// }
