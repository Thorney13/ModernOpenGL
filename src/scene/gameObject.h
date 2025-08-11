#pragma once
#include "rendering/material.h"
#include "rendering/mesh.h"

class GameObject {
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    Mesh* mesh;
    Material* material;

public:
    GameObject(Mesh* mesh, Material* material);
    void setPosition(const glm::vec3& pos);
    void setRotation(const glm::vec3& rot);
    void setScale(const glm::vec3& scale);
    glm::mat4 getModelMatrix() const;
    void draw(const glm::mat4& viewProjection) const;
};