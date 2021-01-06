#include "paddle.h"

Paddle::Paddle(
    Texture2D& texture,
    glm::vec2 pos,
    glm::vec2 size,
    glm::vec3 color,
    glm::vec2 velocity
) : BaseGameObject(texture, pos, size, color, velocity)
{ }
