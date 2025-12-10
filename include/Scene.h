#pragma once

#include "RenderObject.h"
#include <vector>
#include <memory>

class Scene {
public:
    Scene() = default;
    
    void addObject(std::shared_ptr<RenderObject> object);
    void removeObject(std::shared_ptr<RenderObject> object);
    void clear();
    
    const std::vector<std::shared_ptr<RenderObject>>& getObjects() const { return objects; }
    size_t getObjectCount() const { return objects.size(); }

private:
    std::vector<std::shared_ptr<RenderObject>> objects;
};
