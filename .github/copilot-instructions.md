# Farscape Engine - Copilot Instructions

## Project Overview

Farscape Engine is a Vulkan-based 3D game engine designed for handling vast distances and large-scale spaces, particularly focused on space games. The project aims to solve floating-point precision issues when rendering objects at astronomical distances.

### Key Goals
- Handle vast distances seamlessly
- Manage floating-point rounding errors in large-scale rendering
- Focus on space game development
- Provide a clean, cross-platform architecture

## Technology Stack

- **Graphics API**: Vulkan 1.4+
- **Window Management**: GLFW 3.x
- **Math Library**: GLM (header-only)
- **UI Library**: ImGui (docking branch)
- **Build System**: CMake 3.20+
- **Language**: C++17
- **Platforms**: Windows (primary), Linux, macOS

## Project Structure

```
FarscapeEngine/
├── src/                    # Source files (.cpp)
│   ├── main.cpp           # Entry point
│   ├── VulkanApp.cpp      # Main application
│   ├── Renderer.cpp       # Vulkan rendering logic
│   ├── Scene.cpp          # Scene management
│   ├── RenderObject.cpp   # Renderable entity with transforms
│   └── CubeGeometry.cpp   # Geometry utilities
├── include/                # Header files (.h)
│   ├── VulkanApp.h        # Main application header
│   ├── Renderer.h         # Renderer interface
│   ├── Scene.h            # Scene container
│   ├── RenderObject.h     # Render object interface
│   └── CubeGeometry.h     # Geometry utilities
├── shaders/                # GLSL shaders (.vert, .frag)
├── external/               # Third-party dependencies
│   ├── windows/           # Windows-specific binaries
│   │   └── glfw/          # lib-vc2022/ for Visual Studio 2022
│   ├── linux/             # Linux-specific binaries (optional)
│   ├── glm/               # Cross-platform headers
│   └── imgui/             # ImGui UI library (docking branch)
├── build/                  # Build output (not in version control)
├── ARCHITECTURE.md         # Detailed architecture documentation
└── CMakeLists.txt         # Build configuration
```

## Build System Conventions

### CMake Configuration
- **Platform Detection**: Automatically detects Windows/Linux/macOS
- **Library Search Order**:
  1. `external/{platform}/` directories
  2. System package managers (Linux/macOS preferred)
  3. Environment variables (`VULKAN_SDK`, `GLFW_DIR`, `GLM_DIR`)
  4. Standard system paths

### Windows-Specific
- Uses Visual Studio 2022 (MSVC 19.44+)
- GLFW binaries must be in `external/windows/glfw/lib-vc2022/`
- Vulkan SDK path: `C:\VulkanSDK\{version}\`
- Environment variable `VULKAN_SDK` must be set
- Build configuration: Release (primary)

### Linux-Specific
- Prefers system package managers (apt, dnf, pacman)
- Requires X11 libraries
- Links: pthread, dl, X11
- Compiler: GCC/Clang with `-Wall -Wextra -Wpedantic`

### Shader Compilation
- Shaders are compiled to SPIR-V during CMake build
- Compiled shaders output to `build/shaders/` directory
- Uses `glslc` from Vulkan SDK
- Application must run from `build/` directory to find shaders

## Scene/Renderer Architecture

### Design Principles
- **ImGui-first UI**: All interface elements are ImGui windows with full docking support
- **Offscreen rendering**: 3D scene rendered to texture, then displayed in ImGui window
- **Separation of Concerns**: VulkanApp handles lifecycle, Scene manages objects, Renderer handles graphics
- **Flexibility**: Easy to add/remove objects at runtime
- **Encapsulation**: Renderer owns Vulkan buffer lifecycle for objects
- **Extensibility**: RenderObject can be extended for different geometry types

### Rendering Flow
1. Update uniform buffers for current frame
2. Render 3D scene to offscreen texture (renderSceneToTexture)
3. Begin main render pass for swap chain
4. Render ImGui interface (including 3D viewport showing offscreen texture)
5. End render pass and present to swap chain

### Object Lifecycle
1. Create RenderObject with geometry (vertices, indices)
2. Add to Scene via `scene.addObject(object)`
3. Call `renderer.updateScene(&scene)` to create Vulkan buffers
4. Renderer automatically renders all objects in scene
5. Buffers cleaned up when object removed or scene changes

### Transform System
- RenderObjects have position, rotation (Euler angles), and scale
- `getModelMatrix()` computes final transformation matrix
- Currently, first object's transform used for demo rotation
- Future: Per-object uniform buffers for independent transforms

### Adding New Geometry
1. Create static method like `CubeGeometry::getVertices()`
2. Return `std::vector<Vertex>` and `std::vector<uint16_t>`
3. Create RenderObject: `auto obj = std::make_shared<RenderObject>(vertices, indices)`
4. Add to scene: `scene.addObject(obj)`

## Coding Conventions

### File Organization
- Headers in `include/` with `.h` extension
- Implementation in `src/` with `.cpp` extension
- One class per file pair (header + implementation)
- Use `#pragma once` for header guards

### Naming Conventions
- Classes: PascalCase (e.g., `VulkanApp`)
- Methods: camelCase (e.g., `initVulkan`, `createSwapChain`)
- Member variables: camelCase (e.g., `swapChain`, `physicalDevice`)
- Constants: UPPER_SNAKE_CASE (e.g., `MAX_FRAMES_IN_FLIGHT`)

### Vulkan Patterns
- RAII-style resource management
- Explicit initialization order (see `VulkanApp::initVulkan()`)
- Cleanup in reverse order of creation
- Use Vulkan validation layers in debug builds
- Double/Triple buffering for frames in flight

### Error Handling
- Use exceptions for initialization failures
- Runtime errors throw `std::runtime_error` with descriptive messages
- Check Vulkan result codes and throw on failure

## Dependencies Management

### No vcpkg
- Project does not use vcpkg
- All dependencies manually managed in `external/` directory
- Platform-specific binaries kept separate
- ImGui source files included directly in `external/imgui/`

### Windows Setup
1. Vulkan SDK installed system-wide
2. GLFW pre-compiled binaries in `external/windows/glfw/`
3. GLM headers in `external/glm/`
4. ImGui source files in `external/imgui/` (included in repo)

### Linux Setup
- Use system package manager (preferred)
- Manual libraries in `external/linux/` (if needed)
- ImGui source files in `external/imgui/` (included in repo)

## Common Development Workflows

### Building
```powershell
# Windows
$env:VULKAN_SDK = "C:\VulkanSDK\1.4.328.1"
mkdir build; cd build
cmake ..
cmake --build . --config Release
```

### Running
```powershell
# Always run from build directory (for shader access)
cd build
.\Release\Farscape.exe  # Windows
./Farscape              # Linux/macOS
```

### Adding New Source Files
1. Create `.h` in `include/`
2. Create `.cpp` in `src/`
3. Add to `SOURCES` and `HEADERS` lists in `CMakeLists.txt`

### Adding New Shaders
1. Create `.vert` or `.frag` in `shaders/`
2. CMake automatically compiles them to `.spv`
3. Load in code using `readFile("shaders/name.spv")`

## Important Context for AI Assistance

### When Making Changes
- **Always maintain platform separation**: Windows/Linux/macOS
- **Keep CMake cross-platform**: Use platform detection, not hardcoded paths
- **Preserve shader compilation**: Ensure glslc integration works
- **Follow Vulkan best practices**: Proper synchronization, resource lifetimes
- **Test on multiple platforms**: Consider Linux compatibility
- **ImGui integration**: Renderer manages ImGui lifecycle; use separate descriptor pool

### Code Style Preferences
- Prefer explicit over implicit
- Use modern C++17 features
- Keep Vulkan code verbose for clarity
- Comment complex Vulkan setup sequences
- Use consistent indentation (4 spaces)

### Known Issues to Avoid
- Don't run executable from `Release/` directory (shader path issues)
- Don't use vcpkg references
- Don't mix platform-specific binaries
- Don't shadow class member variables with local parameters
- Ensure VULKAN_SDK is set before CMake configuration

### Architecture Decisions
- **ImGui-first interface**: Entire UI is ImGui-based with docking support
- **Offscreen rendering**: 3D scene rendered to texture, displayed in ImGui window
- **Scene/Renderer separation**: Scene manages objects, Renderer handles Vulkan operations
- **RenderObject system**: Objects have geometry and transforms (position, rotation, scale)
- **Per-object buffers**: Renderer creates and manages Vulkan buffers for each object
- **Shared pointers**: Scene uses std::shared_ptr for object lifecycle management
- **Direct game loop**: Simple while loop in mainLoop(), no abstraction yet
- **Single uniform buffer**: Currently one UBO for camera/projection, objects share it
- **No resource manager**: Direct Vulkan handle management
- **Basic scene graph**: Flat list of objects, no parent-child hierarchy yet
- **ImGui docking**: Full docking support with multi-viewport enabled
- **Separate ImGui descriptor pool**: ImGui uses its own descriptor pool to avoid conflicts
- **Dockable 3D viewport**: Scene texture displayed as ImGui::Image in dockable window

## Current Architecture

### Completed
- ✅ **ImGui docking interface**: Full docking support with multi-viewport
- ✅ **Offscreen rendering**: 3D scene rendered to texture for ImGui display
- ✅ **Scene/Renderer separation**: Clean architecture with separated concerns
- ✅ **RenderObject system**: Entities with geometry and transforms
- ✅ **CubeGeometry utility**: Abstracted geometry creation
- ✅ **Per-object buffer management**: Automatic Vulkan buffer lifecycle
- ✅ **Dockable 3D viewport**: Scene displayed as resizable, dockable ImGui window
- ✅ **Background color control**: Interactive RGB color picker in UI

### Key Classes
- **VulkanApp**: Application lifecycle, Vulkan initialization, main loop
- **Renderer**: 
  - Offscreen rendering to texture (renderSceneToTexture)
  - ImGui docking and multi-viewport management
  - Buffer management, camera operations
  - Displays rendered scene via ImGui::Image
- **Scene**: Collection of RenderObjects, add/remove/query operations
- **RenderObject**: Geometry + transforms (position, rotation, scale)
- **CubeGeometry**: Static utility for predefined cube geometry
- **ImGui**: Primary interface with dockable windows (3D Viewport, Scene Controls)

## Future Development Goals

### Short Term
1. Input handling (keyboard/mouse)
2. Camera controller (FPS/orbital)
3. Multiple objects demonstration
4. Per-object uniform buffers for individual transforms
5. Expanded ImGui panels (object inspector, scene hierarchy)

### Medium Term
1. Texture support
2. Material system
3. Basic lighting (Phong)
4. Model loading (.obj, .gltf)
5. Resource management and caching

### Long Term
1. Entity Component System (ECS)
2. Physics integration
3. Hierarchical scene graph
4. PBR rendering
5. Large-scale coordinate system for space rendering
6. Floating-point precision management for vast distances

## Testing & Validation

### Verification Steps
1. Clean build succeeds without errors
2. Application launches and shows ImGui docking interface
3. 3D Viewport window displays rotating cube with correct colors (6 distinct faces)
4. Cube rotates smoothly within viewport window
5. Windows can be docked/undocked and resized
6. Scene Controls panel functions correctly (color picker, FPS counter)
7. Main window resizing works without crashes
8. No Vulkan validation errors in debug mode

### Build Warnings to Ignore
- C4100: Unreferenced parameter (framebuffer resize callback)
- C4458: Declaration hides class member (parameter shadowing)

These are non-critical and can be addressed in future cleanup.

## Communication Preferences

When providing assistance:
- Be concise and direct
- Provide complete code snippets (not partial)
- Include file paths for all changes
- Explain Vulkan-specific concepts when relevant
- Consider cross-platform implications
- Test suggestions against project structure
- Preserve existing working code unless explicitly changing it

## References

- [Vulkan Tutorial](https://vulkan-tutorial.com/) - Primary learning resource
- [Vulkan Specification](https://www.khronos.org/registry/vulkan/)
- [GLFW Documentation](https://www.glfw.org/documentation.html)
- [GLM Documentation](https://github.com/g-truc/glm)
