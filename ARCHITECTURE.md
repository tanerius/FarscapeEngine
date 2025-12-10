# Scene and Renderer Architecture

## Overview

The Farscape Engine has been refactored to separate rendering logic from scene management, making it easier to add and manage multiple objects in the scene.

## Architecture Components

### RenderObject (`RenderObject.h/cpp`)
Represents a single renderable entity in the scene.

**Features:**
- Stores vertex and index data for geometry
- Contains transformation data (position, rotation, scale)
- Provides `getModelMatrix()` to compute the final model transformation matrix

**Usage:**
```cpp
auto cube = std::make_shared<RenderObject>(vertices, indices);
cube->setPosition(glm::vec3(1.0f, 0.0f, 0.0f));
cube->setRotation(glm::vec3(0.0f, glm::radians(45.0f), 0.0f));
cube->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
```

### Scene (`Scene.h/cpp`)
Manages a collection of RenderObjects.

**Features:**
- Add/remove objects from the scene
- Query objects in the scene
- Clear all objects

**Usage:**
```cpp
Scene scene;
auto cube1 = std::make_shared<RenderObject>(cubeVertices, cubeIndices);
auto cube2 = std::make_shared<RenderObject>(cubeVertices, cubeIndices);

scene.addObject(cube1);
scene.addObject(cube2);
scene.removeObject(cube1);
```

### Renderer (`Renderer.h/cpp`)
Handles all Vulkan rendering operations for a scene.

**Features:**
- Creates and manages Vulkan buffers for each object
- Renders all objects in a scene
- Manages camera position and view/projection matrices
- Automatic buffer management when scene changes

**Usage:**
```cpp
Renderer renderer;
renderer.initialize(device, physicalDevice, commandPool, graphicsQueue, ...);
renderer.updateScene(&scene);
renderer.setCamera(glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
renderer.render(commandBuffer, currentFrame, descriptorSets, ...);
```

### CubeGeometry (`CubeGeometry.h/cpp`)
Utility class providing predefined cube geometry.

**Usage:**
```cpp
auto vertices = CubeGeometry::getVertices();
auto indices = CubeGeometry::getIndices();
auto cube = std::make_shared<RenderObject>(vertices, indices);
```

## How It Works

1. **Initialization:**
   - VulkanApp creates a Scene and Renderer
   - Objects are created and added to the scene
   - Renderer is initialized with Vulkan resources
   - Scene is passed to the renderer via `updateScene()`

2. **Rendering Loop:**
   - Each frame, `updateUniformBuffer()` updates object transforms and camera
   - `renderer.render()` renders all objects in the scene
   - Renderer automatically binds correct buffers for each object

3. **Buffer Management:**
   - When `updateScene()` is called, Renderer creates Vulkan buffers for new objects
   - Old buffers are cleaned up when scene changes
   - Each object gets its own vertex and index buffers

## Adding Multiple Objects

To add multiple objects to a scene:

```cpp
// Create multiple cubes with different positions
for (int i = 0; i < 5; i++) {
    auto cube = std::make_shared<RenderObject>(
        CubeGeometry::getVertices(), 
        CubeGeometry::getIndices()
    );
    cube->setPosition(glm::vec3(i * 2.0f, 0.0f, 0.0f));
    scene.addObject(cube);
}

// Update the renderer to create buffers for all objects
renderer.updateScene(&scene);
```

## Future Improvements

### Short Term
- Per-object model matrix updates (currently using global rotation)
- Support for different geometry types
- Material system for per-object colors/textures

### Medium Term
- Instanced rendering for duplicate objects
- Frustum culling
- Level of detail (LOD) system
- Spatial partitioning for large scenes

### Long Term
- Entity Component System (ECS) integration
- Scene graph with parent-child relationships
- Streaming for large scenes
- Multi-threaded rendering

## File Structure

```
include/
├── RenderObject.h    # Renderable entity with transform
├── Scene.h           # Collection of render objects
├── Renderer.h        # Vulkan rendering logic
├── CubeGeometry.h    # Predefined cube geometry
└── VulkanApp.h       # Main application (uses Scene/Renderer)

src/
├── RenderObject.cpp
├── Scene.cpp
├── Renderer.cpp
├── CubeGeometry.cpp
└── VulkanApp.cpp
```

## Migration Notes

**Before:**
- VulkanApp directly managed vertex/index buffers
- Single hardcoded cube
- Rendering logic mixed with application logic

**After:**
- Renderer manages buffers per object
- Scene can contain multiple objects
- Clean separation of concerns
- Easy to add/remove objects at runtime
