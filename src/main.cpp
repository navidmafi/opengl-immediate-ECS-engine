#include <Renderer.hpp>
#include <Scene.hpp>
#include <Cube.hpp>
#include <Clock.hpp>
#include <GameHost.hpp>
#include <fmt/core.h>
#include <chrono>
#include <thread>
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
        .framecap = 150,
        .compat_profile = true};

    GameHost host(window_config);
    OpenGLRenderer renderer(renderer_config);
    Scene scene;
    Clock clock;

    try
    {
        host.hostWindowInit();
        renderer.initializeCtx();
        renderer.initializeGL();

        Cube cube;
        cube.rotation = Rotation{50, 10, 20};
        cube.scale = Scale{0.5, 0.5, 0.5};
        scene.addObj(&cube);

        clock.start();

        while (!glfwWindowShouldClose(host.getWindow()))
        {
            clock.update();
            float deltaTime = clock.getDeltaTime();

            scene.update(deltaTime);

            fmt::println("{}", deltaTime);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            scene.renderScene();

            glfwSwapBuffers(host.getWindow());
            glfwPollEvents();

            if (deltaTime < renderer.targetFrametime())
            {
                double sleepTime = renderer.targetFrametime() - deltaTime;

                long sleepMilliseconds = static_cast<long>(sleepTime * 1000.0);

                if (sleepMilliseconds > 0)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(sleepMilliseconds));
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        fmt::print("Exception: {}\n", e.what());
        return -1;
    }

    glfwDestroyWindow(host.getWindow());
    glfwTerminate();
    return 0;
}
