#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <fmt/core.h>
#include <time.h>
#include <vector>
#include <unistd.h>

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

GLFWwindow *initWindow(void)
{
    GLFWwindow *window;

    fmt::println("initializing glfw");
    if (!glfwInit())
    {
        throw std::runtime_error("failed to init GLFW");
        // return -1;
    }
    fmt::println("glfw init OK");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_WAYLAND_PREFER_LIBDECOR, GL_FALSE);
    glfwWindowHint(GLFW_WAYLAND_LIBDECOR, GL_FALSE);
    glfwWindowHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);
    glfwWindowHint(GLFW_WAYLAND_DISABLE_LIBDECOR, GL_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    fmt::println("creating window");

    window = glfwCreateWindow(640, 480, "glfw", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (!window)
    {
        // glfwTerminate();
        // std::printf(std::to_string(glGetError()).c_str());
        throw std::runtime_error("failed to init window");
        // return -1;
    }

    initGLFWCallbacks(window);

    fmt::println("window init OK");

    return window;
}
void initGL(void)
{
    // Load OpenGL functions, gladLoadGL returns the loaded version, 0 on error.
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        throw std::runtime_error("Failed to initialize OpenGL context");
        // return -1;
    }
    const char *vendor = reinterpret_cast<const char *>(glGetString(GL_VENDOR));     // Returns a hint to the model
    const char *renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER)); // Returns a hint to the model

    const char *glversion = reinterpret_cast<const char *>(glGetString(GL_VERSION));
    // fmt::println("Renderer: OpenGL {}.{} on {}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version),
    // GLAD_VENDOR);

    fmt::println("OpenGL {} on {}", glversion, renderer);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // background color to black
    glClearDepth(1.0f);                   // background depth to farthest
    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);                           // smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // perspective corrections
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

// void RotateDisplay(void (*func)(int))
// {
// }

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

class GameObject
{
public:
    Position position;
    Rotation rotation;
    Scale scale;

    WireMesh mesh = std::vector<Position>();

    virtual void render() = 0;
};

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

int main()
{

    GameHost mainHost(WindowConfig{
        .window_title = "glfw",
        .window_borders = false,
        .resizable = true,
    });

    OpenGLRenderer renderer(RendererConfig{
        .fb_width = 600,
        .fb_height = 600,
        .vsync = false,
        .framecap = 30,
        .compat_profile = true});

    mainHost.hostWindowInit();

    renderer.initializeCtx();
    renderer.initializeGL();

    fmt::println("Exiting cleanly");
    return 0;
}

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
