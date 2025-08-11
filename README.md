# ModernOpenGL

ModernOpenGL is a minimal, modular OpenGL boilerplate using GLFW, GLAD, and CMake. It is designed for learning graphics programming, prototyping, and building the foundation for a rendering engine.

## Installation

Clone the repository and install dependencies using [vcpkg](https://github.com/microsoft/vcpkg):

```bash
vcpkg install glad glfw3
```

## Roadmap

1.	Scene Management System
•	Create a Scene class to organize GameObjects
•	Implement scene graph/hierarchy for parent-child relationships
•	Add methods for object lifecycle (instantiate, destroy)

2.	Resource Management
•	Develop a ResourceManager to load and cache assets
•	Implement resource reference counting
•	Add support for loading models from standard formats (OBJ, FBX)

3.	Rendering Pipeline Improvements
•	Add support for multiple light types (directional, point, spot)
•	Implement basic PBR (Physically Based Rendering)
•	Add post-processing effects (bloom, SSAO, etc.)

4.	Physics Integration
•	Add basic collision detection
•	Implement simple rigid body physics
•	Create physics components for GameObjects

5.	User Interface & Tools
•	Extend ImGui integration for debug tools
•	Create a simple scene editor
•	Add profiling and performance visualization

 - Vulkan backend integration (planned)

## License

[MIT](https://choosealicense.com/licenses/mit/)
