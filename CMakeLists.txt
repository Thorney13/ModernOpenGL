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
    src/utils/fileUtils.cpp
    external/serialPort/serialPort.cpp
    src/utils/arduinoController.cpp
    src/utils/textureUtils.cpp
    src/utils/inputUtils.cpp
    src/utils/cameraUtils.cpp
)

# Now set include directories for your target
target_include_directories(ModernOpenGL PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external/serialPort
)

# Link the OpenGL and GLFW libraries
target_link_libraries(ModernOpenGL PRIVATE glad::glad glfw OpenGL::GL)