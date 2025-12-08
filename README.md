# Farscape Engine

A simple Vulkan-based game engine starting with a rotating cube demo.

## Project Structure

```
FarscapeEngine/
├── src/                  # Source files
│   ├── main.cpp         # Entry point
│   └── VulkanApp.cpp    # Main application implementation
├── include/             # Header files
│   └── VulkanApp.h      # Main application header
├── shaders/             # GLSL shader source files
│   ├── shader.vert      # Vertex shader
│   └── shader.frag      # Fragment shader
├── external/            # Third-party libraries
│   ├── windows/         # Windows-specific binaries
│   │   └── glfw/        # GLFW for Windows
│   ├── linux/           # Linux-specific binaries (if needed)
│   │   └── glfw/        # GLFW for Linux
│   └── glm/             # GLM (header-only, cross-platform)
└── CMakeLists.txt       # CMake build configuration
```

## Prerequisites

Before building the project, you need to install:

1. **Vulkan SDK** - Download from [LunarG Vulkan SDK](https://vulkan.lunarg.com/)
2. **GLFW** - Window and input library
3. **GLM** - OpenGL Mathematics library
4. **CMake** (version 3.20 or higher)
5. **C++ Compiler** with C++17 support (MSVC, GCC, or Clang)

### Windows Installation

1. **Vulkan SDK**
   - Download from [LunarG](https://vulkan.lunarg.com/)
   - Install and it will set the `VULKAN_SDK` environment variable

2. **GLFW** (Window library)
   - Download pre-compiled binaries: [GLFW Downloads](https://www.glfw.org/download.html)
   - Choose "64-bit Windows binaries"
   - Extract to `FarscapeEngine/external/windows/glfw/` (recommended)
     - Should have: `external/windows/glfw/include/` and `external/windows/glfw/lib-vc2022/`
   - Or install to `C:\Program Files\GLFW` or set `GLFW_DIR` environment variable

3. **GLM** (Header-only math library)
   - Download from [GLM GitHub](https://github.com/g-truc/glm/releases)
   - Extract to `FarscapeEngine/external/glm/` (recommended)
     - Should have: `external/glm/glm/glm.hpp`
   - Or install to `C:\Program Files\glm` or set `GLM_DIR` environment variable
   - No compilation needed - it's header-only!

### Linux Installation

**Recommended: Use System Package Manager**

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install vulkan-tools libvulkan-dev vulkan-validationlayers-dev \
                     libglfw3-dev libglm-dev cmake build-essential

# Fedora
sudo dnf install vulkan-tools vulkan-loader-devel vulkan-validation-layers-devel \
                 glfw-devel glm-devel cmake gcc-c++

# Arch Linux
sudo pacman -S vulkan-devel glfw-wayland glm cmake base-devel
```

**Alternative: Manual Installation**
- If you prefer, you can place Linux-specific libraries in `external/linux/glfw/`
- But using system packages is recommended on Linux

### macOS Installation

```bash
brew install vulkan-sdk glfw glm cmake
```

## Building the Project

### Windows (Visual Studio)

**Step 1: Set Vulkan SDK Environment Variable**

The Vulkan SDK must be accessible. If CMake can't find it, set it manually:

```powershell
# Check if VULKAN_SDK is set
$env:VULKAN_SDK

# If not set, set it manually (adjust version number to match your installation)
$env:VULKAN_SDK = "C:\VulkanSDK\1.4.328.1"
```

To set it permanently:
1. Open System Properties → Environment Variables
2. Add `VULKAN_SDK` with value like `C:\VulkanSDK\1.4.328.1`
3. Restart your terminal/IDE

**Step 2: Configure and Build**

```powershell
# Create build directory
mkdir build
cd build

# Configure (CMake will auto-detect libraries in external/ folder)
cmake ..

# Build
cmake --build . --config Release
```

### Linux

```bash
# Install dependencies (if not already installed)
sudo apt-get install vulkan-tools libvulkan-dev vulkan-validationlayers-dev \
                     libglfw3-dev libglm-dev cmake build-essential

# Create build directory
mkdir build
cd build

# Configure
cmake ..

# Build
make -j$(nproc)

# Run
./Farscape
```

### macOS

```bash
# Install dependencies via Homebrew
brew install vulkan-sdk glfw glm cmake

# Create build directory
mkdir build
cd build

# Configure
cmake ..

# Build
make -j$(sysctl -n hw.ncpu)

# Run
./Farscape
```

## Running the Application

**Important:** The executable must be run from the `build` directory so it can find the compiled shaders.

```powershell
# Windows
cd build
.\Release\Farscape.exe

# Linux/macOS
cd build
./Farscape
```

You should see a window titled "Farscape Engine - Rotating Cube" with a 3D cube spinning automatically. Each face has a different color:
- **Front**: Red
- **Back**: Green
- **Top**: Blue
- **Bottom**: Yellow
- **Right**: Magenta
- **Left**: Cyan

The cube rotates continuously around a diagonal axis. Close the window to exit.

## Controls

- Close the window to exit the application
- The cube rotates automatically

## Features

- ✅ Vulkan renderer initialization
- ✅ GLFW window management
- ✅ 3D cube geometry with vertex colors
- ✅ Model-View-Projection (MVP) transformation
- ✅ Automatic rotation animation
- ✅ Depth buffering
- ✅ Swap chain management with window resizing support

## Next Steps

This is a foundational "Hello World" for the Farscape Engine. Possible extensions:

1. Add input handling (keyboard/mouse controls)
2. Implement a camera system
3. Add texture support
4. Create a material system
5. Implement lighting (Phong/PBR)
6. Add more complex geometry
7. Implement an entity component system (ECS)
8. Add physics integration
9. Create a scene graph

## Troubleshooting

### CMake can't find Vulkan
**Solution:**
```powershell
# Windows: Set VULKAN_SDK environment variable
$env:VULKAN_SDK = "C:\VulkanSDK\1.4.328.1"  # Adjust version to your installation

# Or check where it's installed
Get-ChildItem C:\VulkanSDK
```
For permanent fix, add `VULKAN_SDK` to your system environment variables.

### CMake can't find GLFW or GLM
**Windows:**
- Ensure libraries are in `external/windows/glfw/` and `external/glm/`
- Check that GLFW has the correct lib folder: `external/windows/glfw/lib-vc2022/glfw3.lib`

**Linux:**
```bash
sudo apt-get install libglfw3-dev libglm-dev
```

### "Failed to open file: shaders/vert.spv"
**Cause:** Running executable from wrong directory.

**Solution:** Always run from the `build` directory:
```powershell
cd build
.\Release\Farscape.exe  # Windows
./Farscape              # Linux/macOS
```

### Build succeeds but no window appears
- Check if Vulkan drivers are installed for your GPU
- Run `vulkaninfo` to verify Vulkan is working
- Check console output for error messages

### Warnings about shadowed variables
These are harmless compiler warnings that don't affect functionality. They can be ignored or fixed in future updates.

## License

This project is a learning/development foundation. Feel free to use and modify as needed.

## Contributing

This is a personal project, but suggestions and improvements are welcome!
What started as a sandbox testing project for opengl in April 2017, came a long way into an interesting name engine. My initial goal was to experiment with a way to manage vast distances and floating point rounsing errors when rendering vast distanced. 
  
Now, Farscape is a 3D game engine, the purpose of which is to make it easier for the developer to build and work with large landsacpes and vast distances seamlessly. I.e. a game engine with a focus on space games.

### Inspiration
Being a software engineer and an avid gamer myself was enough reason to start experimenting with games and gaming. After countless hours spent downloading and playing around with some commercially available game engine solutions online I started compiling a list of things that I found particularly irritating or difficult to work with using other game engines. It was a coincidence that all of these things were somehow connected to working with objects related to space. I.e. big objects and vast spaces. 

Being a fan of astronomy and the scifi resulted in the name of this project - **Farscape Engine** - after the TV show. 

Together with a combination of the right motivational factors I thought I'd start experimenting with my own implementation of a game engine which will make it easy to do things I found hard or impossible in other game engines. 
