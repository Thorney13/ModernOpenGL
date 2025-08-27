#include "object.h"

Object::Object(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, int vertexFloatCount)
	: VAO(0), VBO(0), EBO(0), vertices(vertices), indices(indices), resourcesFreed(false), vertexSize(vertexFloatCount)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
}

void Object::cleanup() {
	if (!resourcesFreed) {
		if (VAO != 0) {
			glDeleteVertexArrays(1, &VAO);
			VAO = 0;
		}
		if (VBO != 0) {
			glDeleteBuffers(1, &VBO);
			VBO = 0;
		}
		if (EBO != 0) {
			glDeleteBuffers(1, &EBO);
			EBO = 0;
		}
		resourcesFreed = true;
	}
}


Object::~Object() {
}

void Object::draw() const {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}