#include "renderer.h"

Renderer::Renderer() : clearColor(0.1f, 0.1f, 0.15f) {
}

Renderer::~Renderer() {
}

void Renderer::initialize() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Renderer::setClearColor(const glm::vec3& color) {
	clearColor = color;
}

void Renderer::beginFrame() {
	glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(const Scene& scene, float windowWidth, float windowHeight) {

	glViewport(0, 0, windowWidth, windowHeight);

	const_cast<Scene&>(scene).render(windowWidth, windowHeight);
}

void Renderer::endFrame() {
}


