#pragma once
#include "rendering/material.h"
#include "rendering/Object.h"

class GameObject {
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    Object* renderObject;
    Material* material;
    float movementSpeed;
    bool shouldRotate;

public:
    GameObject(Object* renderObject, Material* material);
    ~GameObject();

    void setPosition(const glm::vec3& pos);
    void setRotation(const glm::vec3& rot);
    void setScale(const glm::vec3& scale);
    void cleanup();
    void draw(const glm::mat4& viewProjection) const;

    template<typename T>
    T* getObjectAs() { return dynamic_cast<T*>(renderObject); }

    void processKeyboardInput(int direction, float deltaTime);

    glm::vec3 getPosition() const { return position; }
    glm::mat4 getModelMatrix() const;

    bool shouldAutoRotate() const { return shouldRotate; }
    void setAutoRotate(bool rotate) { shouldRotate = rotate; }


    enum objectMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
};