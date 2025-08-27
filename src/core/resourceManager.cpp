#include "resourceManager.h"
#include "rendering/meshes/cubeNormal.h"
#include "rendering/meshes/cubeSimple.h"
#include "rendering/meshes/planeData.h"

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager::ResourceManager() 
    : shaderPath("../../../src/rendering/shaders/"),
      texturePath("../../../assets/textures/") {
}

ResourceManager::~ResourceManager() {
    cleanup();
}

ResourceManager* ResourceManager::getInstance() {
    if (!instance) {
        instance = new ResourceManager();
    }
    return instance;
}

void ResourceManager::initialize() {
    loadShader("phong", shaderPath + "lighting/phong.vert", shaderPath + "lighting/phong.frag");
    loadShader("default", shaderPath + "shaderToy/default.vert", shaderPath + "shaderToy/default.frag");
    
    createMesh("cube", cubeNormalVertices, cubeNormalIndices);
    createMesh("quad", quadVertices, quadIndices);
    createLight("lightCube", cubeSimpleVertices, cubeSimpleIndices);
    
    createMaterial("defaultLit", getShader("phong"));
    createMaterial("unlit", getShader("default"));
}

void ResourceManager::cleanup() {
    shaders.clear();
    meshes.clear();
    lights.clear();
    materials.clear();
    textures.clear();
}

std::shared_ptr<Shader> ResourceManager::loadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) {
    if (shaders.find(name) != shaders.end()) {
        return shaders[name];
    }
    
    std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexPath, fragmentPath);
    shaders[name] = shader;
    return shader;
}

std::shared_ptr<Shader> ResourceManager::getShader(const std::string& name) {
    auto it = shaders.find(name);
    if (it != shaders.end()) {
        return it->second;
    }
    return nullptr;
}

std::shared_ptr<Mesh> ResourceManager::createMesh(const std::string& name, const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices) {
    if (meshes.find(name) != meshes.end()) {
        return meshes[name];
    }
    
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(vertices, indices);
    meshes[name] = mesh;
    return mesh;
}

std::shared_ptr<Mesh> ResourceManager::getMesh(const std::string& name) {
    auto it = meshes.find(name);
    if (it != meshes.end()) {
        return it->second;
    }
    return nullptr;
}

std::shared_ptr<Light> ResourceManager::createLight(const std::string& name, const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices) {
    if (lights.find(name) != lights.end()) {
        return lights[name];
    }
    
    std::shared_ptr<Light> light = std::make_shared<Light>(vertices, indices);
    lights[name] = light;
    return light;
}

std::shared_ptr<Light> ResourceManager::getLight(const std::string& name) {
    auto it = lights.find(name);
    if (it != lights.end()) {
        return it->second;
    }
    return nullptr;
}

std::shared_ptr<Material> ResourceManager::createMaterial(const std::string& name, std::shared_ptr<Shader> shader) {
    if (materials.find(name) != materials.end()) {
        return materials[name];
    }
    
    std::shared_ptr<Material> material = std::make_shared<Material>(shader.get());
    materials[name] = material;
    return material;
}

std::shared_ptr<Material> ResourceManager::getMaterial(const std::string& name) {
    auto it = materials.find(name);
    if (it != materials.end()) {
        return it->second;
    }
    return nullptr;
}

std::shared_ptr<Texture> ResourceManager::loadTexture(const std::string& name, const std::string& path) {
    if (textures.find(name) != textures.end()) {
        return textures[name];
    }
    
    std::shared_ptr<Texture> texture = std::make_shared<Texture>(path);
    textures[name] = texture;
    return texture;
}

std::shared_ptr<Texture> ResourceManager::getTexture(const std::string& name) {
    auto it = textures.find(name);
    if (it != textures.end()) {
        return it->second;
    }
    return nullptr;
}