#pragma once
#include "rendering/material.h"
#include "rendering/mesh.h"
#include "rendering/lightObject.h"

class GameObject {
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    Mesh* mesh;
    lightObject* light;
    Material* material;
    float movementSpeed;

public:
    GameObject(Mesh* mesh, Material* material);
    GameObject(lightObject* light, Material* material);
    ~GameObject();

    void setPosition(const glm::vec3& pos);
    void setRotation(const glm::vec3& rot);
    void setScale(const glm::vec3& scale);
    void cleanup();
    void draw(const glm::mat4& viewProjection) const;
    bool hasMesh() const { return mesh != nullptr; }
    bool hasLight() const { return light != nullptr; }
    void processKeyboardInput(int direction, float deltaTime);

    glm::vec3 getPosition() const { return position; }
    glm::mat4 getModelMatrix() const;


    enum objectMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
};