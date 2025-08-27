#include "gameObject.h"

GameObject::GameObject(Object* renderObject, Material* material)
	: position(0.0f), rotation(0.0f), scale(1.0f), renderObject(renderObject), material(material), movementSpeed(2.5f), shouldRotate(false) {
}

GameObject::~GameObject() {
	if (renderObject) {
		delete renderObject;
		renderObject = nullptr;
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
	if (material && renderObject) {
		material->use();
		glm::mat4 modelMatrix = getModelMatrix();
		material->setMVP(viewProjection * getModelMatrix());
		material->setModel(modelMatrix);

		renderObject->draw();
	}
}

void GameObject::cleanup() {
	if (renderObject) {
		renderObject->cleanup();
	}
}

void GameObject::processKeyboardInput(int direction, float deltaTime) {
	float velocity = movementSpeed * deltaTime;

	if (direction == FORWARD)
		position += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
	if (direction == BACKWARD)
		position += glm::vec3(0.0f, -1.0f, 0.0f) * velocity;
	if (direction == LEFT)
		position += glm::vec3(-1.0f, 0.0f, 0.0f) * velocity;
	if (direction == RIGHT)
		position += glm::vec3(1.0f, 0.0f, 0.0f) * velocity;
	if (direction == UP)
		position += glm::vec3(0.0f, 0.0f, -1.0f) * velocity;
	if (direction == DOWN)
		position += glm::vec3(0.0f, 0.0f, 1.0f) * velocity;
}