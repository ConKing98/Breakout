#pragma once

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
    void update(float dt);
    void render();

    GameState state;
    unsigned width;
    unsigned height;
    bool keys[1024];
};
