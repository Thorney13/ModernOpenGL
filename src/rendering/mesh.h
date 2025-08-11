#pragma once
#include "utils/glIncludes.h"
#include <vector>

class Mesh {
private:
    GLuint VAO, VBO, EBO;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

public:
    Mesh(const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();
    void draw() const;
};