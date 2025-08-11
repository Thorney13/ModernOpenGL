#pragma once
#include "utils/glIncludes.h"
#include <vector>

const std::vector<GLfloat> pyramidVertices = {
    // Base vertices
    -0.5f, 0.0f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // 0: Back left - red
     0.5f, 0.0f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // 1: Back right - green
     0.5f, 0.0f,  0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // 2: Front right - blue
    -0.5f, 0.0f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f, // 3: Front left - yellow

    // Top vertex
     0.0f, 1.0f,  0.0f,   1.0f, 1.0f, 1.0f,   0.5f, 0.5f  // 4: Top - white
};

const std::vector<GLuint> pyramidIndices = {
    0, 1, 2,
    0, 2, 3,

    // Side faces (4 triangles)
    0, 1, 4,  // Back face
    1, 2, 4,  // Right face
    2, 3, 4,  // Front face
    3, 0, 4   // Left face
};