#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <fmt/core.h>
#include <RendererConfig.hpp>

class OpenGLRenderer
{
private:
    RendererConfig config;
    const char *vendor_name;
    const char *renderer_name;
    const char *gl_version;

    void get_env();

public:
    OpenGLRenderer(RendererConfig config);
    void initializeCtx();
    void initializeGL();
    double targetFrametime();
};

#endif // OPENGLRENDERER_H
