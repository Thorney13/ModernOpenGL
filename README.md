# ModernOpenGL

ModernOpenGL is a minimal, modular OpenGL boilerplate using GLFW, GLAD, and CMake. It is designed for learning graphics programming, prototyping, and building the foundation for a rendering engine.

## Installation

Clone the repository and install dependencies using [vcpkg](https://github.com/microsoft/vcpkg):

```bash
vcpkg install glad glfw3
```

## Build

```bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

## Visual Studio
1. Open the project folder as a CMake project

2. Edit CMakeSettings.json:
```bash
"cmakeToolchain": "C:/Users/YOURNAME/vcpkg/scripts/buildsystems/vcpkg.cmake",
"cmakeCommandArgs": "-DVCPKG_TARGET_TRIPLET=x64-windows"
```
3. Build using the standard Visual Studio build button

## Usage
This project currently renders a single triangle using modern OpenGL (3.3 core profile). It uses VAO/VBOs and shaders defined in code. Further steps will include:

Moving shaders to external files

Adding camera and MVP matrices

Structuring a reusable rendering system

## Roadmap
 - Basic triangle rendering

 - External shader file loading

 - Shader class abstraction

 - MVP matrix and camera support

 - Mesh and renderer class structure

 - Vulkan backend integration (planned)

## License

[MIT](https://choosealicense.com/licenses/mit/)
