cmake_minimum_required(VERSION 3.21)

project(ModernOpenGL)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLFW using vcpkg
find_package(GLFW3 REQUIRED)

find_package(glad REQUIRED)

# Include directories for OpenGL and GLFW
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLFW3_INCLUDE_DIRS})

# Add the source files
add_executable(ModernOpenGL
    src/main.cpp
    
    src/utils/arduino/arduinoController.cpp
    src/rendering/texture.cpp
    src/scene/camera.cpp
    src/utils/profilingUtils.cpp
    src/rendering/shader.cpp
    src/rendering/mesh.cpp
    src/rendering/material.cpp
    src/scene/gameObject.cpp
    src/scene/scene.cpp
    src/rendering/renderer.cpp

    external/serialPort/serialPort.cpp
    external/imgui/imgui.cpp
    external/imgui/imgui_demo.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
)

add_definitions(-DGLFW_INCLUDE_NONE)

# Now set include directories for your target
target_include_directories(ModernOpenGL PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external/serialPort
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/backends
)

# Link the OpenGL and GLFW libraries
target_link_libraries(ModernOpenGL PRIVATE glad::glad glfw OpenGL::GL)