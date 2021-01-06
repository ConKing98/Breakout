#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "object_renderer.h"
#include "../resource/texture/texture2D.h"

class BaseGameObject {
public:
    BaseGameObject(Texture2D& texture, glm::vec2 pos, glm::vec2 size,
        glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f));
    
    virtual void render(ObjectRenderer &renderer);

    void setPosition(glm::vec2 &pos);
    void setSize(glm::vec2 &size);
    void setVelocity(glm::vec2 &velocity);
    void setColor(glm::vec3 &color);
    void setRotation(float rotation);
    void setUnbreakable(bool isUnbreakable);
    void setDestroyed(bool isDestroyed);
    void setTexture(Texture2D &texture);

    const glm::vec2& position() const { return m_position; };
    const glm::vec2& size() const { return m_size; };
    const glm::vec2& velocity() const { return m_velocity; };
    const glm::vec3& color() const { return m_color; };
    float rotation() const { return m_rotation; };
    const Texture2D& texture() const { return m_texture; };
    bool isUnbreakable() const { return m_isUnbreakable; };
    bool isDestroyed() const { return m_isDestroyed; };

private:
    glm::vec2 m_position;
    glm::vec2 m_size;
    glm::vec2 m_velocity;
    glm::vec3 m_color;
    float m_rotation = 0.0f;
    bool m_isUnbreakable = false;
    bool m_isDestroyed = false;
    Texture2D &m_texture;
};
