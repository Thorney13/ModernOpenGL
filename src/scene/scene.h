#pragma once
#include "scene/gameObject.h"
#include "scene/camera.h"
#include <memory>

class Scene {
private:
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    Camera* activeCamera;
    float lastWindowWidth, lastWindowHeight;
    bool usePerspectiveProjection;

public:
	Scene();
	~Scene();

    void addGameObject(std::shared_ptr<GameObject> obj);
    void removeGameObject(std::shared_ptr<GameObject> obj);
    void setActiveCamera(Camera* camera);
    Camera* getActiveCamera() const;
    void update();
    void render(float windowWidth, float windowHeight);
    void toggleProjectionMode();
    void cleanup();
};