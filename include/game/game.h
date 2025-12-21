#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>

#include <vector>
#include <string>

#include "game_objects/ball.h"
#include "game_objects/paddle.h"
#include "game_objects/brick.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Game {
    class Game {
        private:
            GameObject::Paddle m_paddle;
            GameObject::Ball m_ball;
            GameObject::BrickMesh m_brickMesh;

            std::vector<GameObject::Brick> m_bricks;

            glm::mat4 m_view;
            glm::mat4 m_projection;

            void parseLevel(const std::string& levelContent);

        public:
            Game();

            void setVPUniforms();

            void linkBall();
            void linkPaddle();
            void linkBricks(const std::string& levelFilename);
            void linkBrickMesh();

            void drawAllObjects();

            GameObject::Paddle& paddle() { return m_paddle; }
            GameObject::Ball& ball() { return m_ball; }
            glm::mat4& view() { return m_view; }
            glm::mat4& projection() { return m_projection; }
    };
}

#endif
