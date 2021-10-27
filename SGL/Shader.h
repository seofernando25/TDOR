//
// Created by fer on 10/11/2021.
//

#ifndef TDOR_SHADER_H
#define TDOR_SHADER_H


#include "glad.h"
#include <string>
#include <glm/glm.hpp>
#include <SDL2/SDL_log.h>

class Shader {
public:
    char infoLog[1024];
    Shader();
    ~Shader();
    void SetInt(const std::string& name, int value);
    void SetIntArray(const std::string& name, int* values, uint32_t count);
    void SetFloat(const std::string& name, float value);
    void SetVec2(const std::string& name, const glm::vec2& value);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetVec4(const std::string& name, const glm::vec4& value);
    void SetMat3(const std::string &name, const glm::mat3 &value);
    void SetMat4(const std::string& name, const glm::mat4& value);
    bool AddShader(const std::string source, GLuint shaderType);
    bool Validate();
    void Bind();
private:
    bool checkShaderErrors(GLuint shader);
    bool checkProgramErrors(GLuint program);

    GLuint ID;
    bool validated = false;
};


#endif //TDOR_SHADER_H
