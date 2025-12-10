#include "Scene.h"
#include <algorithm>

void Scene::addObject(std::shared_ptr<RenderObject> object) {
    objects.push_back(object);
}

void Scene::removeObject(std::shared_ptr<RenderObject> object) {
    objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
}

void Scene::clear() {
    objects.clear();
}
