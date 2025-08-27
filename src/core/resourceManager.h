#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "rendering/shader.h"
#include "rendering/mesh.h"
#include "rendering/object.h"
#include "rendering/light.h"
#include "rendering/texture.h"
#include "rendering/material.h"

class ResourceManager {
private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
    std::unordered_map<std::string, std::shared_ptr<Mesh>> meshes;
    std::unordered_map<std::string, std::shared_ptr<Light>> lights;
    std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
    std::unordered_map<std::string, std::shared_ptr<Material>> materials;
    
    std::string shaderPath;
    std::string texturePath;
    
    static ResourceManager* instance;
    
    ResourceManager();
    
public:
    ~ResourceManager();
    
    static ResourceManager* getInstance();
    
    void initialize();
    
    void cleanup();
    
    std::shared_ptr<Shader> loadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
    std::shared_ptr<Shader> getShader(const std::string& name);
    
    std::shared_ptr<Mesh> createMesh(const std::string& name, const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
    std::shared_ptr<Mesh> getMesh(const std::string& name);
    
    std::shared_ptr<Light> createLight(const std::string& name, const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
    std::shared_ptr<Light> getLight(const std::string& name);
    
    std::shared_ptr<Material> createMaterial(const std::string& name, std::shared_ptr<Shader> shader);
    std::shared_ptr<Material> getMaterial(const std::string& name);
    
    std::shared_ptr<Texture> loadTexture(const std::string& name, const std::string& path);
    std::shared_ptr<Texture> getTexture(const std::string& name);
    
    void setShaderPath(const std::string& path) { shaderPath = path; }
    void setTexturePath(const std::string& path) { texturePath = path; }
};