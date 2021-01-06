#pragma once

#include "game_level/game_level.h"
#include "game_objects/object_renderer.h"
#include "game_objects/paddle.h"
#include "game_objects/ball.h"

enum GameState {
    ACTIVE,
    MENU,
    WIN,
    LOSS
};

class Game {
public:
    explicit Game(unsigned width, unsigned height);
    ~Game();

    void init();
    void processInput(float dt);
    void processKey(int key, int action);
    void update(float dt);
    void render();

private:
    GameState m_state;
    unsigned m_width;
    unsigned m_height;
    bool m_keys[1024];
    std::vector<GameLevel> m_levels;
    unsigned m_currentLevel;
    ObjectRenderer* m_objectRenderer = nullptr;
    Paddle* m_paddle = nullptr;
    Ball* m_ball = nullptr;
};
