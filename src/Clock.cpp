#include "Clock.hpp"
#include <GLFW/glfw3.h>

Clock::Clock() : lastTime(0), currentTime(0), deltaTime(0) {}

void Clock::start()
{
    lastTime = glfwGetTime();
}

void Clock::update()
{
    currentTime = glfwGetTime();
    deltaTime = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;
}

float Clock::getDeltaTime() const
{
    return deltaTime;
}
