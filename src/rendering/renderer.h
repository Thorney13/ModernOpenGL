#pragma once
#include "scene/scene.h"
#include "core/window.h"

class Renderer {
private:
	glm::vec4 clearColor;

public:

    Renderer();
    ~Renderer();

    void initialize();
    void setClearColor(const glm::vec4& color);

    void beginFrame();
    void render(const Scene& scene, const Window& window);
    void endFrame();
};