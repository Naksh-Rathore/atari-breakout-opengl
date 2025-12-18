#include "game/game.h"

#include <vector>

#include <game_objects/ball.h>
#include <game_objects/paddle.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Game {
    Game::Game()
        : m_ball(0.5f, 72, glm::vec3(0.0f, 0.0f, 0.0f), "assets/shaders/vertex.vs", "assets/shaders/fragment.fs", glm::vec3(1.0f, 1.1f, 0.0f))
        // Clean up later
        , m_paddle(std::vector<GLfloat> { 200.0f, 50.0f, 0.0f, 1.0f, 1.0f,  200.0f, -50.0f, 0.0f, 1.0f, 0.0f,  -200.0f, -50.0f, 0.0f, 0.0f, 0.0f,  -200.0f, 50.0f, 0.0f, 0.0f, 1.0f }, glm::vec3(0.0f, -300.0f, 0.0f), "assets/shaders/vertex.vs", "assets/shaders/fragment.fs", 2.0f )
        , m_view(glm::mat4(1.0f))
        , m_projection(glm::ortho(-400.0f, 400.0f, -400.0f, 400.0f))
    {
    }

    void Game::setVPUniforms() {
        m_ball.shader().use();

        m_ball.shader().setMatrixUniform("view", m_view);
        m_ball.shader().setMatrixUniform("projection", m_projection);

        m_paddle.shader().use();

        m_paddle.shader().setMatrixUniform("view", m_view);
        m_paddle.shader().setMatrixUniform("projection", m_projection);
    }

    void Game::linkBall() {
        m_ball.circle().generateVertices(100.0f, true);

        m_ball.linkShape();
        m_ball.linkShaders();
        m_ball.linkTextures("assets/textures/ball.png");
    }

    void Game::linkPaddle() {
        m_paddle.linkShape();
        m_paddle.linkShaders();
        m_paddle.linkTextures("assets/textures/paddle.png");
    }

    void Game::drawAllObjects() {
        m_paddle.shader().use();
        m_paddle.render();

        m_ball.shader().use();
        m_ball.update(m_paddle, 500, 200);
        m_ball.render();
    }
}
