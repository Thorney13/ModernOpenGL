#pragma once
#include "object.h"

class Light : public Object {
public:
    Light(const std::vector<GLfloat>& vertices, const std::vector<unsigned int>& indices);
    ~Light() override;
};