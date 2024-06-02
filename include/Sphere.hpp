#ifndef SPHERE_H
#define SPHERE_H

#include <GameObject.hpp>

class Sphere : public GameObject
{
public:
    Sphere();
    ~Sphere() override;
    void render() override;
    void update(float deltaTime) override;
};

#endif // SPHERE_H
