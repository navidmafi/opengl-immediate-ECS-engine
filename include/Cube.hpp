#ifndef CUBE_H
#define CUBE_H

#include <GameObject.hpp>

class Cube : public GameObject
{
public:
    Cube();
    ~Cube() override;
    void render() override;
    void update(float deltaTime) override;
};

#endif // CUBE_H
