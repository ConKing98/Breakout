#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>

class Shader {
public:
    explicit Shader();
    ~Shader();

    int id() const;
    void use();
    void compile(const char* vertexSource, const char* shaderSource, const char* geometrySource = nullptr);

    template <typename Type>
    void setUniform(const std::string &name, const Type &val1);
    template <typename Type>
    void setUniform(const std::string &name, const Type &val1, const Type &val2);
    template <typename Type>
    void setUniform(const std::string &name, const Type &val1, const Type &val2, const Type &val3);
    template <typename Type>
    void setUniform(const std::string &name, const Type &val1, const Type &val2, const Type &val3, const Type &val4);

private:
    struct ShaderMetaData {
        const GLenum glId;
        const GLchar* debugName;
    };

    int linkProgram(const std::vector<GLuint> &shaders);
    int compileShader(const GLuint shader, const GLchar* source, const GLchar* debugName);
    
    static void error(const GLchar* level, const GLchar* summary, const GLchar* errorMessage);

    const unsigned m_id;
    const unsigned m_bufferSize = 1024;

    static const std::vector<ShaderMetaData> m_supportedShaders;
};

#include "shader.tpp"
