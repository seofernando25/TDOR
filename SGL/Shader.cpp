//
// Created by fer on 10/11/2021.
//

#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>


Shader::Shader() {
    ID = glCreateProgram();
}

bool Shader::AddShader(const std::string source, GLuint shaderType) {
    if (validated){
        SDL_LogInfo(SDL_LOG_CATEGORY_RENDER,  "Shader has already been validated");
        return false;
    }

    auto shader = glCreateShader(shaderType);
    const char* shaderSource = source.c_str();
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);
    bool ok = checkShaderErrors(shader);
    if (ok){
        glAttachShader(ID, shader);
        glDeleteShader(shader);
    }
    return ok;
}

bool Shader::Validate(){
    glLinkProgram(ID);
    bool ok = checkProgramErrors(ID);
    validated = ok;
    return ok;
}



bool Shader::checkProgramErrors(GLuint program) {
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success){
        glGetProgramInfoLog(program, 1024, nullptr, infoLog);
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Program linking failed:\n%s", infoLog);
    }
    return success;
}

bool Shader::checkShaderErrors(GLuint shader) {
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Shader compilation failed:\n%s", infoLog);
    }
    return success;
}


void Shader::SetInt(const std::string &name, int value) {
    GLint location = glGetUniformLocation(ID, name.c_str());
    glUniform1i(location, value);
}

void Shader::SetIntArray(const std::string &name, int *values, uint32_t count) {
    GLint location = glGetUniformLocation(ID, name.c_str());
    glUniform1iv(location, count, values);
}

void Shader::SetFloat(const std::string &name, float value) {
    GLint location = glGetUniformLocation(ID, name.c_str());
    glUniform1f(location, value);
}

void Shader::SetVec2(const std::string &name, const glm::vec2 &value) {
    GLint location = glGetUniformLocation(ID, name.c_str());
    glUniform2f(location, value.x, value.y);
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &value) {
    GLint location = glGetUniformLocation(ID, name.c_str());
    glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetVec4(const std::string &name, const glm::vec4 &value) {
    GLint location = glGetUniformLocation(ID, name.c_str());
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::SetMat3(const std::string &name, const glm::mat3 &value) {
    GLint location = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &value) {
    GLint location = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

Shader::~Shader() {
    glDeleteProgram(ID);
    ID = 0;
}

void Shader::Bind() {
    glUseProgram(ID);
}
