#pragma once
#include "scene/scene.h"

class Renderer {
private:
	glm::vec3 clearColor;

public:

    Renderer();
    ~Renderer();

    void initialize();
    void setClearColor(const glm::vec3& color);

    void beginFrame();
    void render(const Scene& scene, float windowWidth, float windowHeight);
    void endFrame();
};