#pragma once

#include <glad/glad.h>

#include "texture/texture2D.h"
#include "shader/shader.h"

#include <unordered_map>
#include <string>

class ResourceManager {
public:
    ResourceManager(ResourceManager const&) = delete;
    ~ResourceManager();

    void operator=(ResourceManager const&) = delete;

    static ResourceManager& getInstance();

    Shader& loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath, const std::string &geometryPath = "");
    Shader& getShader(const std::string &name) const;
    Texture2D& loadTexture(const std::string &name, const std::string &path);
    Texture2D& getTexture(const std::string &name) const;

    void clear();

private:
    ResourceManager() {};

    Shader* loadShaderFromFile(const std::string &vertexPath, const std::string &fragmentPath, const std::string &geometryPath = "");
    Texture2D* loadTextureFromFile(const std::string &path);

    static void error(const GLchar* level, const GLchar* summary, const GLchar* message);

    std::unordered_map<std::string, Shader*> m_shaders;
    std::unordered_map<std::string, Texture2D*> m_textures;
};
