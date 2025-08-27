#include "light.h"

Light::Light(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices)
	: Object(vertices, indices, 3)
{

}

Light::~Light() {
}
