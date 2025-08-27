#include "lightObject.h"

lightObject::lightObject(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices)
	: Object(vertices, indices, 3)
{

}

lightObject::~lightObject() {
}
