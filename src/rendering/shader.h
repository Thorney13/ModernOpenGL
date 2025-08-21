#pragma once
#include "utils/glIncludes.h"
#include <string>

class Shader {
private:

    unsigned int ID;
    
    void checkCompileErrors(GLuint shader, const std::string& type);

public:

    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    
    ~Shader();
    
    // Activate the shader program
    void use() const;
    
    // Utility functions for setting uniforms
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setMat4(const std::string& name, const glm::mat4& matrix) const;
    
    // Getter for the shader ID
    unsigned int getID() const { return ID; }
};