# External Dependencies Directory

This directory contains platform-specific third-party libraries.

## Directory Structure

```
external/
├── windows/          # Windows-specific binaries
│   └── glfw/         # GLFW precompiled for Windows
│       ├── include/  # Header files
│       └── lib/      # .lib files
├── linux/            # Linux-specific binaries (optional)
│   └── glfw/         # GLFW precompiled for Linux (if not using system packages)
│       ├── include/
│       └── lib/
├── macos/            # macOS-specific binaries (optional)
│   └── glfw/
│       ├── include/
│       └── lib/
└── glm/              # GLM (header-only, cross-platform)
    └── glm/          # GLM headers
        └── glm.hpp
```

## Setup Instructions

### Windows
1. Download GLFW from https://www.glfw.org/download.html (64-bit Windows binaries)
2. Extract to `external/windows/glfw/`
3. Download GLM from https://github.com/g-truc/glm/releases
4. Extract to `external/glm/`

### Linux
Use system package manager (recommended):
```bash
sudo apt-get install libglfw3-dev libglm-dev
```

Or place precompiled libraries in `external/linux/glfw/` if needed.

### macOS
Use Homebrew (recommended):
```bash
brew install glfw glm
```

Or place precompiled libraries in `external/macos/glfw/` if needed.

## Notes
- GLM is header-only and cross-platform, so only one copy is needed
- GLFW binaries are platform-specific due to different OS APIs
- On Linux/macOS, using system package managers is generally preferred
- CMake will automatically search platform-specific directories first
