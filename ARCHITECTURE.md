# Scene and Renderer Architecture

## Overview

The Farscape Engine features an ImGui-first dockable interface architecture with offscreen rendering. The 3D scene is rendered to a texture and displayed within a dockable ImGui window, allowing for a fully customizable workspace layout.

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
Handles all Vulkan rendering operations for a scene and manages the ImGui docking interface.

**Features:**
- **Offscreen Rendering**: Renders 3D scene to texture for display in ImGui
- Creates and manages Vulkan buffers for each object
- Manages offscreen render pass, framebuffer, and texture resources
- Manages camera position and view/projection matrices
- Automatic buffer management when scene changes
- **ImGui Docking**: Full docking support with multi-viewport
- Separate descriptor pool for ImGui to avoid resource conflicts
- Dynamic background color control via UI
- Dockable 3D viewport window

**Usage:**
```cpp
Renderer renderer;
renderer.initialize(device, physicalDevice, commandPool, graphicsQueue, ...);
renderer.createOffscreenRenderPass(colorFormat, depthFormat);
renderer.createOffscreenResources(colorFormat, depthFormat);
renderer.initializeImGui(window, instance, renderPass, graphicsQueue, imageCount);
renderer.updateScene(&scene);
renderer.setCamera(glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

// In render loop
renderer.renderSceneToTexture(commandBuffer, currentFrame, descriptorSets, ...);
renderer.newImGuiFrame();  // Start ImGui frame with dockspace
renderer.renderImGui(commandBuffer);  // Render UI with 3D viewport
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
   - ImGui is initialized with a separate descriptor pool
   - Scene is passed to the renderer via `updateScene()`

2. **Rendering Loop:**
   - Each frame, `updateUniformBuffer()` updates object transforms and camera
   - `renderer.renderSceneToTexture()` renders 3D scene to offscreen texture
   - Main render pass begins for swap chain
   - `renderer.newImGuiFrame()` starts ImGui frame with dockspace
   - `renderer.renderImGui()` renders UI (including 3D viewport showing texture)
   - Renderer automatically binds correct buffers for each object

3. **Buffer Management:**
   - When `updateScene()` is called, Renderer creates Vulkan buffers for new objects
   - Old buffers are cleaned up when scene changes
   - Each object gets its own vertex and index buffers
   - Offscreen framebuffer and texture managed by Renderer
   - ImGui uses a separate descriptor pool to avoid conflicts with scene rendering

4. **UI Features:**
   - **Dockable Interface**: Full docking support with multi-viewport
   - **3D Viewport Window**: Displays rendered scene texture as ImGui image
   - **Scene Controls Panel**: Real-time background color picker, FPS counter
   - **Menu Bar**: File menu with application controls
   - **Resizable Viewports**: 3D viewport can be resized and docked anywhere

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

## Current UI Features (ImGui Docking)

The engine features a fully dockable ImGui interface as the primary user interface:

**Dockable Windows:**
- **3D Viewport**: Displays rendered scene texture, resizable and dockable
- **Scene Controls Panel**: Background color picker, FPS counter, frame time
- **Menu Bar**: File menu with Exit option
- **Dockspace**: Main docking area for flexible layout

**Implementation Details:**
- ImGui uses separate descriptor pool (avoids conflicts with main rendering)
- Backends: `imgui_impl_glfw` and `imgui_impl_vulkan`
- Offscreen rendering: Scene rendered to texture, then displayed in ImGui
- Full docking support with `ImGuiConfigFlags_DockingEnable`
- Multi-viewport support with `ImGuiConfigFlags_ViewportsEnable`
- Scene texture sampled via ImGui descriptor set

## Future Improvements

### Short Term
- Input handling (keyboard/mouse for camera control)
- Camera controller (FPS/orbital modes)
- Multiple objects demonstration
- Per-object uniform buffers for individual transforms
- Expanded ImGui panels (object inspector, scene hierarchy)
- Transform controls via ImGui

### Medium Term
- Instanced rendering for duplicate objects
- Frustum culling
- Level of detail (LOD) system
- Spatial partitioning for large scenes
- Material system for per-object colors/textures
- Model loading (.obj, .gltf)

### Long Term
- Entity Component System (ECS) integration
- Scene graph with parent-child relationships
- Streaming for large scenes
- Multi-threaded rendering
- PBR rendering pipeline
- Large-scale coordinate system for space rendering
- Floating-point precision management for vast distances

## File Structure

```
include/
├── RenderObject.h    # Renderable entity with transform
├── Scene.h           # Collection of render objects
├── Renderer.h        # Vulkan rendering logic + ImGui integration
├── CubeGeometry.h    # Predefined cube geometry
└── VulkanApp.h       # Main application (uses Scene/Renderer)

src/
├── RenderObject.cpp
├── Scene.cpp
├── Renderer.cpp      # Includes ImGui initialization and rendering
├── CubeGeometry.cpp
├── VulkanApp.cpp
└── main.cpp          # Entry point

external/
├── imgui/            # ImGui library (docking branch)
│   ├── imgui.cpp     # Core ImGui files
│   ├── imgui.h
│   └── backends/     # GLFW and Vulkan backends
├── glm/              # Math library (header-only)
└── windows/glfw/     # Platform-specific GLFW binaries

shaders/
├── shader.vert       # Vertex shader (GLSL)
└── shader.frag       # Fragment shader (GLSL)
```

## Migration Notes

**Version 1 (Initial):**
- VulkanApp directly managed vertex/index buffers
- Single hardcoded cube
- Rendering logic mixed with application logic

**Version 2 (Scene/Renderer):**
- Renderer manages buffers per object
- Scene can contain multiple objects
- Clean separation of concerns
- Simple ImGui overlay

**Version 3 (Current - ImGui Docking):**
- Offscreen rendering to texture
- Full ImGui docking interface
- 3D viewport as dockable window
- Multi-viewport support
- Flexible workspace layouts
