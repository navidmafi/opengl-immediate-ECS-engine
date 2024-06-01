#include <Scene.hpp>

void Scene::addObj(GameObject *obj)
{
    objects.push_back(obj);
}

void Scene::update(float deltaTime)
{
    for (auto *obj : objects)
    {
        obj->update(deltaTime);
    }
}

void Scene::renderScene()
{
    for (auto *obj : objects)
    {
        obj->render();
    }
}
