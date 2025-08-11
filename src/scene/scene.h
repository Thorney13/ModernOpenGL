#pragma once
#include "scene/gameObject.h"
#include "scene/camera.h"

class Scene {
private:
    std::vector<GameObject*> gameObjects;
    Camera* activeCamera;

public:
	Scene();
	~Scene();

    void addGameObject(GameObject* obj);
    void removeGameObject(GameObject* obj);
    void setActiveCamera(Camera* camera);
    Camera* getActiveCamera() const;
    void update();
    void render(float windowWidth, float windowHeight);
};