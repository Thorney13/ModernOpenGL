#include "scene.h"

Scene::Scene() : activeCamera(nullptr) {
}

Scene::~Scene() {
}

void Scene::addGameObject(GameObject* obj) {
	if (obj) {
		gameObjects.push_back(obj);
	}
}

void Scene::removeGameObject(GameObject* obj) {
	auto it = std::find(gameObjects.begin(), gameObjects.end(), obj);
	if (it != gameObjects.end()) {
		gameObjects.erase(it);
	}
}

void Scene::setActiveCamera(Camera* camera) {
	activeCamera = camera;
}

Camera* Scene::getActiveCamera() const {
	return activeCamera;
}

void Scene::update() {
	for (auto& obj : gameObjects) {
		if (obj) {
			float currentTime = (float)glfwGetTime();
			float rotationSpeed = 20.0f;
			float rotationAngle = rotationSpeed * currentTime;

			obj->setRotation(glm::vec3(rotationAngle, rotationAngle, rotationAngle));
			obj->getModelMatrix();
		}
	}
}

void Scene::render(float windowWidth, float windowHeight) {
	if (!activeCamera) return;

	glm::mat4 view = activeCamera->getViewMatrix();
	glm::mat4 projection = activeCamera->getProjectionMatrix((float)windowWidth / (float)windowHeight);

	glm::mat4 viewProjection = projection * view;
	
	for (auto& obj : gameObjects) {
			obj->draw(viewProjection);
	}
}