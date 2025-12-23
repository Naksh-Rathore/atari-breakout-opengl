#include "game/game.h"

#include <vector>
#include <fstream>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game_objects/ball.h"
#include "game_objects/paddle.h"
#include "game_objects/brick.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Game {
    Game::Game()
        : m_ball(0.5f, 72, glm::vec3(0.0f, 0.0f, 0.0f), "assets/shaders/ball_paddle/vertex.vs", "assets/shaders/ball_paddle/fragment.fs", glm::vec3(700.0f, 800.1f, 0.0f))
        // Clean up later
        , m_paddle(std::vector<GLfloat> { 200.0f, 50.0f, 0.0f, 1.0f, 1.0f,  200.0f, -50.0f, 0.0f, 1.0f, 0.0f,  -200.0f, -50.0f, 0.0f, 0.0f, 0.0f,  -200.0f, 50.0f, 0.0f, 0.0f, 1.0f }, glm::vec3(0.0f, -300.0f, 0.0f), "assets/shaders/ball_paddle/vertex.vs", "assets/shaders/ball_paddle/fragment.fs", 600.0f )
        , m_brickMesh(glm::vec3(0.0f, 0.0f, 0.0f))
        , m_view(glm::mat4(1.0f))
        , m_projection(glm::ortho(-400.0f, 400.0f, -400.0f, 400.0f))
        , m_deltaTime(0.0f)
        , m_lastFrame(0.0f)
    {
    }

    void Game::setVPUniforms() {
        m_ball.shader().use();

        m_ball.shader().setMatrixUniform("view", m_view);
        m_ball.shader().setMatrixUniform("projection", m_projection);

        m_paddle.shader().use();

        m_paddle.shader().setMatrixUniform("view", m_view);
        m_paddle.shader().setMatrixUniform("projection", m_projection);

        m_brickMesh.shader().use();

        m_brickMesh.shader().setMatrixUniform("view", m_view);
        m_brickMesh.shader().setMatrixUniform("projection", m_projection);
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

    void Game::linkBrickMesh() {
        m_brickMesh.rect().link();
        m_brickMesh.linkShader();
    }

    void Game::linkBricks(const std::string& levelFilename) {
        std::ifstream levelFileStream("assets/levels/" + levelFilename);
        
        std::string levelContent;
        std::string levelContentBuffer;

        while (std::getline(levelFileStream, levelContentBuffer)) {
            levelContent += levelContentBuffer + "\n"; 
        }

        levelFileStream.close();

        parseLevel(levelContent);
    }

    void Game::parseLevel(const std::string& levelContent) {
        glm::vec3 position { glm::vec3(-300.0f, 300.0f, 0.0f) };

        for (auto character : levelContent) {
            if (character == '\n') {
                position.y -= 100.0f;
                position.x = -300.0f;

                continue;
            }

            switch (character) {
                case '0':
                    position.x += 125.0f;
                    break;

                case '1':
                    m_bricks.emplace_back(position, glm::vec3(1.0f, 1.0f, 1.0f), false);
                    position.x += 125.0f;   
                    break;

                case '2':
                    m_bricks.emplace_back(position, glm::vec3(1.0f, 0.0f, 0.0f));
                    position.x += 125.0f;
                    break;
                
                case '3':
                    m_bricks.emplace_back(position, glm::vec3(0.0f, 1.0f, 0.0f));
                    position.x += 125.0f;
                    break;

                case '4':
                    m_bricks.emplace_back(position, glm::vec3(0.0f, 0.0f, 1.0f));
                    position.x += 125.0f;
                    break;
            }
        }
    }

    void Game::drawAllObjects() {
        float currentFrame { glfwGetTime() };

        m_deltaTime = currentFrame - m_lastFrame;
        m_lastFrame = currentFrame;  

        for (GameObject::Brick &brick : m_bricks) {
            if (brick.isDestroyed() && brick.isDestroyable())
                continue;

            brick.update(m_ball);

            m_brickMesh.render(brick.modelMatrix(), brick.color());
        }

        m_paddle.render();

        m_ball.update(m_paddle, 500, 200, m_deltaTime);
        m_ball.render();
    }
}
