#include "shader.h"

#include <sstream>
#include <fstream>
#include <stdio.h>

#define VERTEX_SHADER_NAME "VERTEX"
#define FRAGMENT_SHADER_NAME "FRAGMENT"
#define GEOMETRY_SHADER_NAME "GEOMETRY"

const std::vector<Shader::ShaderMetaData> Shader::m_supportedShaders {
    {GL_VERTEX_SHADER,   VERTEX_SHADER_NAME},
    {GL_FRAGMENT_SHADER, FRAGMENT_SHADER_NAME},
    {GL_GEOMETRY_SHADER, GEOMETRY_SHADER_NAME}
};

Shader::Shader() : m_id(glCreateProgram()) { }

Shader::~Shader() {
    glDeleteProgram(m_id);
}

void Shader::compile(
    const char* vertexSource,
    const char* fragmentSource,
    const char* geometrySource
) {
    if (!vertexSource || !fragmentSource) {
        error("FILE", "NULLPTR_SOURCE", "Vertex and fragment shader data required");
        return;
    }

    std::vector<unsigned> shaderIds;
    std::vector<const char*> shaderSources{vertexSource, fragmentSource};
    if (geometrySource)
        shaderSources.push_back(geometrySource);

    for (unsigned i = 0; i < shaderSources.size(); i++) {
        shaderIds.emplace_back(glCreateShader(m_supportedShaders[i].glId));
        compileShader(shaderIds.back(), shaderSources[i], m_supportedShaders[i].debugName);
    }

    linkProgram(shaderIds);

    for (const GLuint &shaderId : shaderIds) {
        glDeleteShader(shaderId);
    }
}

int Shader::id() const {
    return m_id;
}

void Shader::use() {
    glUseProgram(m_id);
}

int Shader::linkProgram(const std::vector<GLuint> &shaders) {
    for (const auto &shader : shaders) {
        glAttachShader(m_id, shader);
    }
    glLinkProgram(m_id);

    int success;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[m_bufferSize];
        glGetProgramInfoLog(m_id, m_bufferSize, NULL, infoLog);
        error("PROGRAM", "LINKING_FAILED", infoLog);
    }
    return success;
}

int Shader::compileShader(
    const GLuint shader,
    const GLchar* source,
    const GLchar* name
) {
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[m_bufferSize];
        glGetShaderInfoLog(shader, m_bufferSize, NULL, infoLog);
        error(name, "COMPILATION_FAILED", infoLog);
    }
    return success;
}

void Shader::error(
    const GLchar* level,
    const GLchar* summary,
    const GLchar* message
) {
    fprintf(stderr, "ERROR::SHADER::%s::%s\n%s\n", level, summary, message);
}
