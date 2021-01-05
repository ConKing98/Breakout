#include "resource_manager.h"

#include <sstream>
#include <fstream>

#include "stb/stb_image.h"

ResourceManager::~ResourceManager() {
    clear();
}

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

Shader& ResourceManager::loadShader(
    const std::string &name,
    const std::string &vertexPath,
    const std::string &fragmentPath,
    const std::string &geometryPath
) {
    auto iter = m_shaders.find(name);
    Shader* prior = (iter != m_shaders.end()) ? (*iter).second : nullptr;
    m_shaders[name] = loadShaderFromFile(vertexPath, fragmentPath, geometryPath);
    delete prior;
    return *m_shaders[name];
}

Shader& ResourceManager::getShader(const std::string &name) const {
    return *m_shaders.at(name);
}

Texture2D& ResourceManager::loadTexture(
    const std::string &name,
    const std::string &path,
    bool alpha
) {
    auto iter = m_textures.find(name);
    Texture2D* prior = (iter != m_textures.end()) ? (*iter).second : nullptr;
    m_textures[name] = loadTextureFromFile(path, alpha);
    delete prior;
    return *m_textures[name];
}

Texture2D& ResourceManager::getTexture(const std::string &name) const {
    return *m_textures.at(name);
}

void ResourceManager::clear() {
    for (auto &iter : m_shaders)
        delete iter.second;
    for (auto &iter : m_textures)
        delete iter.second;
    m_shaders.clear();
    m_textures.clear();
}

Shader* ResourceManager::loadShaderFromFile(
    const std::string &vertexPath,
    const std::string &fragmentPath,
    const std::string &geometryPath
) {
    if (vertexPath.empty() || fragmentPath.empty()) {
        error("SHADER", "EMPTY_PATH", "Vertex and fragment shader paths required");
        return nullptr;
    }

    std::vector<std::string> paths{vertexPath, fragmentPath};
    if (!geometryPath.empty())
        paths.push_back(geometryPath);
    std::vector<std::string> sourceCode;

    try {
        for (const std::string &path : paths) {
            std::ifstream shaderFile(path);
            std::stringstream dataStream;
            dataStream << shaderFile.rdbuf();
            shaderFile.close();
            sourceCode.push_back(dataStream.str());
        }
    } catch (std::exception &e) {
        error("SHADER", "READ_FAILURE", e.what());
    }

    Shader* shader = new Shader();
    shader->compile(sourceCode[0].c_str(), sourceCode[1].c_str(),
        (sourceCode.size() > 2) ? sourceCode[2].c_str() : nullptr);
    return shader;
}

Texture2D* ResourceManager::loadTextureFromFile(const std::string &path, bool alpha) {
    Texture2D* texture = new Texture2D();
    if (alpha) {
        texture->setInternalFormat(GL_RGBA);
        texture->setImageFormat(GL_RGBA);
    }

    int width;
    int height;
    int numChannels;
    unsigned char* textureData = stbi_load(path.c_str(), &width, &height, &numChannels, 0);
    texture->generate(width, height, numChannels, textureData);
    stbi_image_free(textureData);
    return texture;
}

void ResourceManager::error(
    const GLchar* level,
    const GLchar* summary,
    const GLchar* message
) {
    fprintf(stderr, "RESOURCE_MANAGER::%s::%s\n%s\n", level, summary, message);
}
