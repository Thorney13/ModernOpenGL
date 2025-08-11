#pragma once
#include "utils/glIncludes.h"

static const GLfloat cubeVertices[] = {
    // Front face (red)
   -0.5f, -0.5f,  0.5f,  1.f, 0.f, 0.f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.f, 0.f, 0.f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f,  1.0f, 1.0f,
   -0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f,  0.0f, 1.0f,

    // Back face (green)
   -0.5f, -0.5f, -0.5f,  0.f, 1.f, 0.f,  1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  0.f, 1.f, 0.f,  0.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f,  0.0f, 1.0f,
   -0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f,  1.0f, 1.0f,

    // Left face (blue)
    -0.5f, -0.5f, -0.5f,  0.f, 0.f, 1.f,  0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.f, 0.f, 1.f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.f, 0.f, 1.f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.f, 0.f, 1.f,  0.0f, 1.0f,

    // Right face (yellow)
    0.5f, -0.5f,  0.5f,  1.f, 1.f, 0.f,  1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.f, 1.f, 0.f,  0.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.f, 1.f, 0.f,  0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.f, 1.f, 0.f,  1.0f, 1.0f,

    // Top face (magenta)
   -0.5f,  0.5f,  0.5f,  1.f, 0.f, 1.f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.f, 0.f, 1.f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.f, 0.f, 1.f,  1.0f, 1.0f,
   -0.5f,  0.5f, -0.5f,  1.f, 0.f, 1.f,  0.0f, 1.0f,
    // Bottom face (cyan)
   -0.5f, -0.5f,  0.5f,  0.f, 1.f, 1.f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.f, 1.f, 1.f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.f, 1.f, 1.f,  0.0f, 0.0f,
   -0.5f, -0.5f, -0.5f,  0.f, 1.f, 1.f,  1.0f, 0.0f
};

static const GLuint cubeIndices[] = {
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