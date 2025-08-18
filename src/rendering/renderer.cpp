#include "renderer.h"

Renderer::Renderer() : clearColor(0.1f, 0.1f, 0.15f, 1.0f) {
}

Renderer::~Renderer() {
}

void Renderer::initialize() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Renderer::setClearColor(const glm::vec4& color) {
	clearColor = color;
}

void Renderer::beginFrame() {
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(const Scene& scene, const Window& window) {

	float windowWidth = static_cast<float>(window.getWidth());
	float windowHeight = static_cast<float>(window.getHeight());

	const_cast<Scene&>(scene).render(windowWidth, windowHeight);
}

void Renderer::endFrame() {
}


