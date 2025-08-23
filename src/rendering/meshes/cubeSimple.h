#pragma once
#include "utils/glIncludes.h"
#include <vector>

const std::vector<GLfloat> cubeSimpleVertices = {
    // Front face (red)
   -0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
   -0.5f,  0.5f,  0.5f,

    // Back face (green)
   -0.5f, -0.5f, -0.5f, 
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
   -0.5f,  0.5f, -0.5f,

    // Left face (blue)
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,

    // Right face (yellow)
    0.5f, -0.5f,  0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f,  0.5f,

    // Top face (magenta)
   -0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f, -0.5f,
   -0.5f,  0.5f, -0.5f,
    // Bottom face (cyan)
   -0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f, -0.5f, -0.5f,
   -0.5f, -0.5f, -0.5f,
};

static std::vector<GLuint> cubeSimpleIndices = {
    // Front face
    0,  1,  2,  2,  3,  0,
    // Back face
    4,  5,  6,  6,  7,  4,
    // Left face
    8,  9, 10, 10, 11,  8,
    // Right face
    12, 13, 14, 14, 15, 12,
    // Top face
    16, 17, 18, 18, 19, 16,
    // Bottom face
    20, 21, 22, 22, 23, 20
};