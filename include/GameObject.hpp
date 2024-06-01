#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <Vec3.hpp>
#include <Face.hpp>

class GameObject
{
public:
    Position position;
    Rotation rotation;
    Scale scale;
    std::vector<Face> faces;

    GameObject();
    virtual ~GameObject() = default;
    virtual void render() = 0;
    virtual void update(float deltaTime) = 0;
};

#endif // GAMEOBJECT_H
