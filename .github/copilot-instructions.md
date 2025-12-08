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
- **Build System**: CMake 3.20+
- **Language**: C++17
- **Platforms**: Windows (primary), Linux, macOS

## Project Structure

```
FarscapeEngine/
├── src/                    # Source files (.cpp)
├── include/                # Header files (.h)
├── shaders/                # GLSL shaders (.vert, .frag)
├── external/               # Third-party dependencies
│   ├── windows/           # Windows-specific binaries
│   │   └── glfw/          # lib-vc2022/ for Visual Studio 2022
│   ├── linux/             # Linux-specific binaries (optional)
│   └── glm/               # Cross-platform headers
├── build/                  # Build output (not in version control)
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

### Windows Setup
1. Vulkan SDK installed system-wide
2. GLFW pre-compiled binaries in `external/windows/glfw/`
3. GLM headers in `external/glm/`

### Linux Setup
- Use system package manager (preferred)
- Manual libraries in `external/linux/` (if needed)

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
- **No game loop abstraction yet**: Direct while loop in mainLoop()
- **Single VulkanApp class**: Currently monolithic, will be refactored
- **Fixed cube geometry**: Hardcoded in VulkanApp, will be abstracted
- **No resource manager**: Direct Vulkan handle management
- **No scene graph**: Single rotating cube demo only

## Future Development Goals

### Short Term
1. Input handling (keyboard/mouse)
2. Camera system with controls
3. Abstract geometry loading
4. Separate renderer class

### Medium Term
1. Texture support
2. Material system
3. Basic lighting (Phong)
4. Resource management
5. Multiple objects/entities

### Long Term
1. Entity Component System (ECS)
2. Physics integration
3. Scene graph
4. PBR rendering
5. Large-scale coordinate system for space rendering
6. Floating-point precision management for vast distances

## Testing & Validation

### Verification Steps
1. Clean build succeeds without errors
2. Application launches and shows window
3. Cube renders with correct colors (6 distinct faces)
4. Cube rotates smoothly
5. Window resizing works without crashes
6. No Vulkan validation errors in debug mode

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
