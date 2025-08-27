#include "mesh.h"

Mesh::Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices)
	: Object(vertices, indices, 6)
{
	glBindVertexArray(VAO);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

Mesh::~Mesh() {

}

void Mesh::draw() const {
	glBindVertexArray(VAO);
	if (indices.empty()) {
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size() / 6));
	}
	else {
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
}