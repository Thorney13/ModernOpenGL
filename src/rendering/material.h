#pragma once
#include "texture.h"
#include "shader.h"
#include <map>

class Material {
private:
    Shader* shader;
    std::map<std::string, Texture> textures;

public:
    Material(Shader* shader);
    void addTexture(const std::string& uniformName, const Texture& texture);
    void use() const;
    void setMVP(const glm::mat4& mvp);
    void setModel(const glm::mat4& model);
};