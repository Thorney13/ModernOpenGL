#include "scene.h"

Scene::Scene() : activeCamera(nullptr), lastWindowWidth(0), lastWindowHeight(0), usePerspectiveProjection(true) {
}

Scene::~Scene() {
}

void Scene::addGameObject(std::shared_ptr<GameObject> obj) {
	if (obj) {
		gameObjects.push_back(obj);
	}
}

void Scene::removeGameObject(std::shared_ptr<GameObject> obj) {
	auto it = std::find(gameObjects.begin(), gameObjects.end(), obj);
	if (it != gameObjects.end()) {
		gameObjects.erase(it);
	}
}

void Scene::setActiveCamera(Camera* camera) {
	activeCamera = camera;
	if (activeCamera && lastWindowWidth > 0 && lastWindowHeight > 0) {
		//activeCamera->setPerspective(45.0f, (float)lastWindowWidth / (float)lastWindowHeight, 0.1f, 100.0f);
		activeCamera->setOrthographic(20.0f, 20.0f, 0.1f, 100.0f);
	}

}

Camera* Scene::getActiveCamera() const {
	return activeCamera;
}

void Scene::update() {
	for (auto& obj : gameObjects) {
		if (obj && obj->shouldAutoRotate()) {
			float currentTime = (float)glfwGetTime();
			float rotationSpeed = 20.0f;
			float rotationAngle = rotationSpeed * currentTime;

			obj->setRotation(glm::vec3(rotationAngle, rotationAngle, rotationAngle));
			}
		}
}

void Scene::toggleProjectionMode() {
	if (!activeCamera) return;

	usePerspectiveProjection = !usePerspectiveProjection;

	if (usePerspectiveProjection) {
		// Switch to perspective
		activeCamera->setPerspective(70.0f,
			(float)lastWindowWidth / (float)lastWindowHeight,
			0.1f, 100.0f);
	}
	else {
		// Switch to orthographic
		// Calculate distance to origin to determine appropriate size
		float distance = glm::length(activeCamera->getPosition());
		float orthoSize = distance * 0.5f; // Adjust this multiplier as needed

		activeCamera->setOrthographic(
			orthoSize * ((float)lastWindowWidth / (float)lastWindowHeight),
			orthoSize,
			0.1f, 100.0f);
	}
}

void Scene::render(float windowWidth, float windowHeight) {
	if (!activeCamera) return;

	if (windowWidth != lastWindowWidth || windowHeight != lastWindowHeight) {
		lastWindowWidth = windowWidth;
		lastWindowHeight = windowHeight;

		// Update current projection with new aspect ratio
		if (usePerspectiveProjection) {
			activeCamera->setPerspective(70.0f,
				windowWidth / windowHeight, 0.1f, 100.0f);
		}
		else {
			float distance = glm::length(activeCamera->getPosition());
			float orthoSize = distance * 0.5f;
			activeCamera->setOrthographic(
				orthoSize * (windowWidth / windowHeight),
				orthoSize,
				0.1f, 100.0f);
		}
	}

	glm::mat4 view = activeCamera->getViewMatrix();
	glm::mat4 projection = activeCamera->getProjectionMatrix();
	glm::mat4 viewProjection = projection * view;
	
	for (auto& obj : gameObjects) {
			obj->draw(viewProjection);
	}
}

// Add this method to your Scene class
void Scene::cleanup() {
	for (auto& gameObject : gameObjects) {
		if (gameObject) {
			gameObject->cleanup();
		}
	}
}