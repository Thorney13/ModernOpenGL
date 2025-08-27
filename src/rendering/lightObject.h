#pragma once
#include "object.h"

class lightObject : public Object {
public:
    lightObject(const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices);
    ~lightObject() override;
};