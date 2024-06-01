#ifndef SCENE_H
#define SCENE_H

#include <list>
#include <GameObject.hpp>
#include <RGBAC.hpp>

class Scene
{
private:
    std::list<GameObject *> objects;

public:
    RGBAC background;
    void addObj(GameObject *obj);
    void update(float deltaTime);
    void renderScene();
};

#endif // SCENE_H
