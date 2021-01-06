#pragma once

#include "../game_objects/base_game_object.h"

#include <vector>

enum TileCodes {
    EMPTY,
    UNBREAKABLE,
    NORMAL_WHITE,
    NORMAL_RED,
    NORMAL_ORANGE,
    NORMAL_YELLOW,
    NORMAL_GREEN,
    NORMAL_BLUE,
    NORMAL_INDIGO,
    NORMAL_VIOLET,
    NORMAL_BLACK,
    NUM_TILE_CODES
};

class GameLevel {
public:
    GameLevel() { };
    GameLevel(const char* path, unsigned width, unsigned height);

    void load(const char* path, unsigned width, unsigned height);
    void render(ObjectRenderer &renderer);
    bool isComplete() const;

    std::vector<BaseGameObject>& bricks() { return m_bricks; };

private:
    void init(std::vector<std::vector<unsigned>> tileData,
        unsigned levelWidth, unsigned levelHeight);

    static glm::vec3 colorForTileCode(int code);
    static void error(const GLchar* level, const GLchar* summary, const GLchar* errorMessage);

    std::vector<BaseGameObject> m_bricks;
};
