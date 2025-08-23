#include "gameObject.h"

GameObject::GameObject(Mesh* mesh, Material* material)
	: position(0.0f), rotation(0.0f), scale(1.0f), mesh(mesh), light(nullptr), material(material) {
}

GameObject::GameObject(lightObject* light, Material* material)
	: position(0.0f), rotation(0.0f), scale(1.0f), mesh(nullptr), light(light), material(material) {
}

GameObject::~GameObject() {
	if (mesh) {
		delete mesh;
		mesh = nullptr;
	}

	if (light) {
		delete light;
		light = nullptr;
	}

	if (material) {
		delete material;
		material = nullptr;
	}
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
	if (material) {
		material->use();
		glm::mat4 modelMatrix = getModelMatrix();
		material->setMVP(viewProjection * getModelMatrix());
		material->setModel(modelMatrix);

		if (mesh) {
			mesh->draw();
		}
		else if (light) {
			light->draw();
		}
	}
}

void GameObject::cleanup() {
	if (mesh) {
		mesh->cleanup();
	}
	if (light) {
		light->cleanup();
	}
}