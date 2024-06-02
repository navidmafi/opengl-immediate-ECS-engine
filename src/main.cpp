#include <Renderer.hpp>
#include <Scene.hpp>
#include <Cube.hpp>
#include <Sphere.hpp>
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
        .framecap = 30,
        .compat_profile = true};

    GameHost host(window_config);
    OpenGLRenderer renderer(renderer_config);
    host.onResize(std::bind(&OpenGLRenderer::changeFBSize, &renderer, std::placeholders::_1, std::placeholders::_2));
    Scene scene;
    Clock clock;

    try
    {
        host.hostWindowInit();
        renderer.initializeCtx();
        renderer.initializeGL();
        glfwSetWindowUserPointer(host.getWindow(), &host);

        Cube cube;
        cube.position = Position{-0.2, -0.2, 0.5};
        cube.rotation = Rotation{0, 20, 20};
        cube.scale = Scale{0.1, 0.5, 0.5};
        scene.addObj(&cube);

        Sphere sphere;
        sphere.position = Position{0.8, 0.5, 1};
        sphere.rotation = Rotation{50, 10, 20};
        sphere.scale = Scale{0.5, 0.5, 0.5};
        scene.addObj(&sphere);

        Sphere sphere2;
        sphere2.position = Position{-0.8, 0.5, 1};
        sphere2.rotation = Rotation{50, 10, 20};
        sphere2.scale = Scale{0.5, 0.5, 0.5};
        scene.addObj(&sphere2);

        clock.start();

        while (!glfwWindowShouldClose(host.getWindow()))
        {
            clock.update();
            float deltaTime = clock.getDeltaTime();

            scene.update(deltaTime);

            fmt::println("frametime {}ms", static_cast<int>(deltaTime * 1000));

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
