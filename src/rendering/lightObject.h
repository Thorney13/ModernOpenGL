#pragma once
#include "utils/glIncludes.h"
#include <vector>

class lightObject {
private:
    GLuint VAO, VBO, EBO;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    bool resourcesFreed;

public:
    lightObject(const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices);
    ~lightObject();
    void draw() const;
    void cleanup();
};