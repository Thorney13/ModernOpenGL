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
#include_directories(include)

# Add the source files
add_executable(ModernOpenGL	src/main.cpp "src/utils/fileUtils.h" "src/utils/fileUtils.cpp")

# Link the OpenGL and GLFW libraries
target_link_libraries(ModernOpenGL PRIVATE glad::glad glfw OpenGL::GL)