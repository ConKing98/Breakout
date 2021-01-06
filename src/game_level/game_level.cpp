#include "game_level.h"

#include <string>
#include <fstream>
#include <sstream>

#include "../resource/resource_manager.h"

GameLevel::GameLevel(const char* path, unsigned width, unsigned height) {
    load(path, width, height);
}

void GameLevel::load(const char* path, unsigned width, unsigned height) {
    m_bricks.clear();

    std::ifstream fileData(path);
    if (!fileData) {
        error("LOAD", "READ_FAILURE", path);
        return;
    }

    std::vector<std::vector<unsigned>> tiles;
    std::vector<unsigned> tileRow;
    unsigned tileData;

    std::string line;
    while (std::getline(fileData, line)) {
        std::istringstream lineStream(line);
        while (lineStream >> tileData)
            tileRow.push_back(tileData);
        tiles.push_back(tileRow);
        tileRow.clear();
    }

    if (tiles.empty()) {
        error("LOAD", "EMPTY_FILE", "No level data found");
        return;
    }

    init(tiles, width, height);
}

void GameLevel::render(ObjectRenderer &renderer) {
    for (auto &tile : m_bricks) {
        if (!tile.isDestroyed())
            tile.render(renderer);
    }
}

bool GameLevel::isComplete() const {
    for (const auto &tile : m_bricks) {
        if (!tile.isUnbreakable() && !tile.isDestroyed())
            return false;
    }
    return true;
}

void GameLevel::init(
    std::vector<std::vector<unsigned>> tileData,
    unsigned levelWidth,
    unsigned levelHeight
) {
    unsigned height = tileData.size();
    unsigned width = tileData[0].size();
    float widthRatio = levelWidth / static_cast<float>(width);
    float heightRatio = levelHeight / static_cast<float>(height);

    const auto &rm = ResourceManager::getInstance();
    auto &textureUnbreakable = rm.getTexture("unbreakable_brick");
    auto &textureNormal = rm.getTexture("normal_brick");

    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            glm::vec3 color(colorForTileCode(tileData[y][x]));
            if (color.x == -1)
                continue;

            glm::vec2 pos(widthRatio * x, heightRatio * y);
            glm::vec2 size(widthRatio, heightRatio);

            if (tileData[y][x] == TileCodes::UNBREAKABLE) {
                m_bricks.emplace_back(pos, size, textureUnbreakable, color);
                m_bricks.back().setUnbreakable(true);
            } else {
                m_bricks.emplace_back(pos, size, textureNormal, color);
            }
        }
    }
}

glm::vec3 GameLevel::colorForTileCode(int code) {
    switch (code) {
    case TileCodes::EMPTY:         return glm::vec3(-1.0f);
    case TileCodes::UNBREAKABLE:   return glm::vec3(0.5f, 0.5f, 0.5f);
    case TileCodes::NORMAL_WHITE:  return glm::vec3(1.0f, 1.0f, 1.0f);
    case TileCodes::NORMAL_RED:    return glm::vec3(1.0f, 0.0f, 0.0f);
    case TileCodes::NORMAL_ORANGE: return glm::vec3(1.0f, 0.5f, 0.0f);
    case TileCodes::NORMAL_YELLOW: return glm::vec3(1.0f, 1.0f, 0.0f);
    case TileCodes::NORMAL_GREEN:  return glm::vec3(0.0f, 1.0f, 0.0f);
    case TileCodes::NORMAL_BLUE:   return glm::vec3(0.0f, 0.2f, 1.0f);
    case TileCodes::NORMAL_INDIGO: return glm::vec3(0.5f, 0.0f, 1.0f);
    case TileCodes::NORMAL_VIOLET: return glm::vec3(1.0f, 0.0f, 1.0f);
    case TileCodes::NORMAL_BLACK:  return glm::vec3(0.0f, 0.0f, 0.0f);
    default: {
        error("TILE_CODE", "UNRECOGNIZED", std::to_string(code).c_str());
        return glm::vec3(-1.0f);
    }
    }
}

void GameLevel::error(
    const GLchar* level,
    const GLchar* summary,
    const GLchar* errorMessage
) {
    fprintf(stderr, "ERROR::GAME_LEVEL::%s::%s\n%s\n", level, summary, errorMessage);
}
