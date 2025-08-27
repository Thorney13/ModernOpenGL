#pragma once
#include "object.h"

class Mesh : public Object {
public:
    Mesh(const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh() override;
    void draw() const override;
};