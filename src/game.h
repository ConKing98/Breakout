#pragma once

#include "game_objects/object_renderer.h"

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
    ObjectRenderer *m_objectRenderer = nullptr;
};
