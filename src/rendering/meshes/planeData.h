#pragma once
#include "utils/glIncludes.h"
#include <vector>

const std::vector<GLfloat> quadVertices = {
-1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,   // Top left
-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,   // Bottom left
 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,   // Bottom right
 1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f    // Top right
};

static std::vector<GLuint> quadIndices = {
0, 1, 2,
0, 2, 3
};