#ifndef CLOCK_H
#define CLOCK_H

class Clock
{
private:
    double lastTime;
    double currentTime;
    float deltaTime;

public:
    Clock();
    void start();
    void update();
    float getDeltaTime() const;
};

#endif // CLOCK_H
