#pragma once
#include "utils/glIncludes.h"
#include <vector>

class Object {
protected:
    GLuint VAO, VBO, EBO;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    bool resourcesFreed;
    int vertexSize;

public:
    Object(const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices, int vertexFloatCount = 3);
    virtual ~Object();
    virtual void draw() const;
    void cleanup();
};