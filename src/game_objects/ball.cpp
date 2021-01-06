#include "ball.h"

Ball::Ball(Texture2D& texture, glm::vec2 pos, float radius, glm::vec2 velocity)
    : BaseGameObject(texture, pos, {radius * 2, radius * 2})
    , m_radius(radius)
{
    setVelocity(velocity);
}

const glm::vec2& Ball::move(float dt, unsigned windowWidth) {
    if (!m_stuck) {
        m_position += m_velocity * dt;
        if (m_position.x <= 0.0f) {
            m_position.x = 0.0f;
            m_velocity.x = -m_velocity.x;
        } else if (m_position.x + m_size.x >= windowWidth) {
            m_position.x = windowWidth - m_size.x;
            m_velocity.x = -m_velocity.x;
        }
        if (m_position.y <= 0.0f) {
            m_position.y = 0.0f;
            m_velocity.y = -m_velocity.y;
        }
    }
    return m_position;
}

void Ball::reset(glm::vec2 position, glm::vec2 velocity) {
     m_position = position;
     m_velocity = velocity;
     m_stuck = true;
}

void Ball::setRadius(float radius) {
    m_radius = radius;
}
