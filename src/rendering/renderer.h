#pragma once
#include "scene/scene.h"
#include "core/window.h"

class Renderer {
private:
	glm::vec3 clearColor;

public:

    Renderer();
    ~Renderer();

    void initialize();
    void setClearColor(const glm::vec3& color);

    void beginFrame();
    void render(const Scene& scene, const Window& window);
    void endFrame();
};