#pragma once

#include "base_game_object.h"

class Paddle : public BaseGameObject {
public:
    Paddle(Texture2D& texture, glm::vec2 pos, glm::vec2 size = glm::vec2(100.0f, 20.0f),
        glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(500.0f, 0.0f));
};
