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
    if (m_paddle)
        delete m_paddle;
    if (m_ball)
        delete m_ball;
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
    rm.loadTexture("ball", "textures/ball.png");

    // Load levels
    m_currentLevel = 0;
    m_levels.emplace_back("levels/one.lvl", m_width, m_height >> 1);

    // Load paddle
    m_paddle = new Paddle(rm.getTexture("paddle"), {0.0f, 0.0f});
    glm::vec2 paddlePos = glm::vec2(
        m_width / 2.0f - m_paddle->size().x / 2.0f,
        m_height - m_paddle->size().y
    );
    m_paddle->setPosition(paddlePos);

    // Load ball
    m_ball = new Ball(rm.getTexture("ball"), {0.0f, 0.0f});
    glm::vec2 ballPos = paddlePos + glm::vec2(
        m_paddle->size().x / 2.0f - m_ball->radius(),
        -m_ball->radius() * 2.0f
    );
    m_ball->setPosition(ballPos);
}

void Game::processInput(float dt) {
    if (m_state == GameState::ACTIVE) {
        // Move the paddle left and/or right. If the ball has not yet been
        // released (it's still stuck), then update the ball position as well
        bool left = m_keys[GLFW_KEY_A] || m_keys[GLFW_KEY_LEFT];
        bool right = m_keys[GLFW_KEY_D] || m_keys[GLFW_KEY_RIGHT];
        float distance = m_paddle->velocity().x * dt * (right - left);
        // Update paddle position
        auto paddlePos = glm::vec2(m_paddle->position());
        paddlePos.x += distance;
        paddlePos.x = std::max(paddlePos.x, 0.0f);
        paddlePos.x = std::min(paddlePos.x, m_width - m_paddle->size().x);
        m_paddle->setPosition(paddlePos);
        // Update the ball position if stuck to the paddle
        if (m_ball->isStuck()) {
            const float paddleCenter = m_paddle->size().x / 2.0f;
            auto ballPos = glm::vec2(m_ball->position());
            ballPos.x += distance;
            ballPos.x = std::max(ballPos.x, paddleCenter - m_ball->radius());
            ballPos.x = std::min(ballPos.x, m_width - paddleCenter - m_ball->radius());
            m_ball->setPosition(ballPos);
        }

        // Release the ball if the space key is pressed
        if (m_ball->isStuck() && m_keys[GLFW_KEY_SPACE]) {
            m_ball->unstuck();
        }
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
    m_ball->move(dt, m_width);
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

        // Render the ball
        m_ball->render(*m_objectRenderer);
    }
}
