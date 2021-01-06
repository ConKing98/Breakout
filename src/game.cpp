#include "game.h"

#include "resource/resource_manager.h"

Game::Game(unsigned width, unsigned height)
    : m_state(GameState::ACTIVE)
    , m_width(width)
    , m_height(height)
    , m_keys()
{ }

Game::~Game() {
    if (m_objectRenderer)
        delete m_objectRenderer;
    m_objectRenderer = nullptr;
}

void Game::init() {
    auto &rm = ResourceManager::getInstance();
    auto &shader = rm.loadShader("HELLO!", "shaders/sprite.vs", "shaders/sprite.fs");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_width),
        static_cast<float>(m_height), 0.0f, -1.0f, 1.0f);
    shader.use();
    shader.setUniform("projection", projection);
    shader.setUniform("image", 0);

    m_objectRenderer = new ObjectRenderer(shader);

    // Load textures
    rm.loadTexture("normal_brick", "textures/brick.png");
    rm.loadTexture("unbreakable_brick", "textures/unbreakable.png");
    rm.loadTexture("background", "textures/background.png");
    rm.loadTexture("circle", "textures/circle.png");

    // Load levels
    m_currentLevel = 0;
    m_levels.emplace_back("levels/one.lvl", m_width, m_height >> 1);
}

void Game::processInput(float dt) {

}

void Game::processKey(int key, int action) {
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            m_keys[key] = true;
        } else if (action == GLFW_RELEASE) {
            m_keys[key] = false;
        }
    }
}

void Game::update(float dt) {

}

void Game::render() {
    if (m_state == GameState::ACTIVE) {
        // Render the background
        m_objectRenderer->render(ResourceManager::getInstance().getTexture("background"),
            glm::vec2(0.0f), glm::vec2(m_width, m_height));
        
        // Render the level
        m_levels[m_currentLevel].render(*m_objectRenderer);
    }
}
