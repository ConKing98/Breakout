#include "game.h"

#include "resource/resource_manager.h"
#include "game_objects/paddle.h"

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
    rm.loadTexture("paddle", "textures/paddle.png");

    // Load levels
    m_currentLevel = 0;
    m_levels.emplace_back("levels/one.lvl", m_width, m_height >> 1);

    m_paddle = new Paddle(rm.getTexture("paddle"), {0.0f, 0.0f});
    glm::vec2 playerPos = glm::vec2(
        m_width / 2.0f - m_paddle->size().x / 2.0f,
        m_height - m_paddle->size().y
    );
    m_paddle->setPosition(playerPos);
}

void Game::processInput(float dt) {
    if (m_state == GameState::ACTIVE) {
        float distance = m_paddle->velocity().x * dt;
        bool left = m_keys[GLFW_KEY_A] || m_keys[GLFW_KEY_LEFT];
        bool right = m_keys[GLFW_KEY_D] || m_keys[GLFW_KEY_RIGHT];

        auto position = glm::vec2(m_paddle->position());
        position.x += distance * (right - left);
        position.x = std::max(position.x, 0.0f);
        position.x = std::min(position.x, m_width - m_paddle->size().x);
        m_paddle->setPosition(position);
    }
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

        // Render the paddle
        m_paddle->render(*m_objectRenderer);
    }
}
