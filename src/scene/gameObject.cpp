#include "gameObject.h"

GameObject::GameObject(Mesh* mesh, Material* material)
	: position(0.0f), rotation(0.0f), scale(1.0f), mesh(mesh), material(material) {
}

void GameObject::setPosition(const glm::vec3& pos) {
	position = pos;
}

void GameObject::setRotation(const glm::vec3& rot) {
	rotation = rot;
}

void GameObject::setScale(const glm::vec3& scale) {
	this->scale = scale;
}

glm::mat4 GameObject::getModelMatrix() const {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, scale);
	return model;
}

void GameObject::draw(const glm::mat4& viewProjection) const {
	if (mesh && material) {
		material->use();
		material->setMVP(viewProjection * getModelMatrix());
		mesh->draw();
	}
}