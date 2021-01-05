#include "game.h"

#include "resource/resource_manager.h"

Game::Game(unsigned width, unsigned height)
    : m_state(GameState::MENU)
    , m_width(width)
    , m_height(height)
    , m_keys()
{ }

Game::~Game() {
    if (m_sprite)
        delete m_sprite;
    m_sprite = nullptr;
}

void Game::init() {
    auto &rm = ResourceManager::getInstance();
    auto &shader = rm.loadShader("HELLO!", "shaders/sprite.vs", "shaders/sprite.fs");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_width),
        static_cast<float>(m_height), 0.0f, -1.0f, 1.0f);
    shader.use();
    shader.setUniform("projection", projection);
    shader.setUniform("image", 0);

    m_sprite = new Sprite(shader);
    rm.loadTexture("circle", "textures/circle.png", true);
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
    m_sprite->draw(ResourceManager::getInstance().getTexture("circle"),
        glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
