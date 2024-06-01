#include <Renderer.hpp>

OpenGLRenderer::OpenGLRenderer(RendererConfig config) : config(config), vendor_name(nullptr), renderer_name(nullptr), gl_version(nullptr) {}

void OpenGLRenderer::get_env()
{
    vendor_name = reinterpret_cast<const char *>(glGetString(GL_VENDOR));
    renderer_name = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
    gl_version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
}

void OpenGLRenderer::initializeCtx()
{
    if (!gladLoadGL(glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize OpenGL context");
    }
    get_env();
    fmt::print("OpenGL {} on {}\n", gl_version, renderer_name);
}

void OpenGLRenderer::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
