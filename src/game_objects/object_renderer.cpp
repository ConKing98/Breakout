#include "object_renderer.h"

ObjectRenderer::ObjectRenderer(Shader &shader) : m_shader(shader) {
    initRenderData();
}

ObjectRenderer::~ObjectRenderer() {
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}

void ObjectRenderer::render(
    Texture2D &texture,
    const glm::vec2 &position,
    glm::vec2 size,
    float rotation,
    glm::vec3 color
) {
    m_shader.use();
    glm::mat4 model = glm::mat4(1.0f);
    // Translate.
    model = glm::translate(model, glm::vec3(position, 0.0f));
    // Rotate. Translate first to shift the origin of rotation to the center.
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    // Scale.
    model = glm::scale(model, glm::vec3(size, 1.0f));

    m_shader.setUniform("model", model);
    m_shader.setUniform("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void ObjectRenderer::initRenderData() {
    static const float vertices[] = {
        // pos      // texture
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(m_VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
