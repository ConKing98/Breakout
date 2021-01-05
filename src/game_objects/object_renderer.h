#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../resource/shader/shader.h"
#include "../resource/texture/texture2D.h"

class ObjectRenderer {
public:
    ObjectRenderer(Shader &shader);
    ~ObjectRenderer();

    void render(
        Texture2D &texture,
        const glm::vec2 &position,
        glm::vec2 size = glm::vec2(10.0f, 10.0f),
        float rotation = 0.0f,
        glm::vec3 color = glm::vec3(1.0f)
    );
private:
    void initRenderData();

    Shader &m_shader;
    unsigned m_VAO;
    unsigned m_VBO;
};
