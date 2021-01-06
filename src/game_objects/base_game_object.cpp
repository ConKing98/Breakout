#include "base_game_object.h"

BaseGameObject::BaseGameObject(
    Texture2D& texture,
    glm::vec2 pos,
    glm::vec2 size,
    glm::vec3 color,
    glm::vec2 velocity
) : m_position(pos)
  , m_size(size)
  , m_velocity(velocity)
  , m_color(color)
  , m_texture(texture)
{ }

void BaseGameObject::setPosition(glm::vec2 &pos) {
    m_position = pos;
}

void BaseGameObject::setSize(glm::vec2 &size) {
    m_size = size;
}

void BaseGameObject::setVelocity(glm::vec2 &velocity) {
    m_velocity = velocity;
}

void BaseGameObject::setColor(glm::vec3 &color) {
    m_color = color;
}

void BaseGameObject::setRotation(float rotation) {
    m_rotation = rotation;
}

void BaseGameObject::setUnbreakable(bool isUnbreakable) {
    m_isUnbreakable = isUnbreakable;
}

void BaseGameObject::setDestroyed(bool isDestroyed) {
    m_isDestroyed = isDestroyed;
}

void BaseGameObject::setTexture(Texture2D &texture) {
    m_texture = texture;
}

void BaseGameObject::render(ObjectRenderer &renderer) {
    renderer.render(m_texture, m_position, m_size, m_rotation, m_color);
}
