#pragma once

#include "base_game_object.h"

class Ball : public BaseGameObject {
public:
    Ball(Texture2D& texture, glm::vec2 pos, float radius = 12.5f,
        glm::vec2 velocity = glm::vec2(100.0f, -350.0f));

    const glm::vec2& move(float dt, unsigned windowWidth);
    void reset(glm::vec2 position, glm::vec2 velocity);
    void unstuck() { m_stuck = false; };

    void setRadius(float radius);

    float radius() const { return m_radius; };
    bool isStuck() const { return m_stuck; };

private:
    float m_radius;
    bool m_stuck = true;
};
