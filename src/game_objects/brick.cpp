#include <vector>
#include <iostream>

#include <glad/glad.h>

#include <glm/glm.hpp>

#include "game_objects/brick.h"
#include "game_objects/ball.h"

#include "collisions/collisions.h"

namespace GameObject {
    BrickMesh::BrickMesh(const glm::vec3& pos)
        : m_rect(m_vertices, pos, m_indices, 3)
        , m_vert("assets/shaders/brick/vertex.vs", GL_VERTEX_SHADER)
        , m_frag("assets/shaders/brick/fragment.fs", GL_FRAGMENT_SHADER)
        , m_shader()
    {}

    void BrickMesh::linkShader() {
        m_vert.compileShader();
        m_frag.compileShader();

        m_shader.link(m_vert, m_frag);
    }

    void BrickMesh::render(const glm::mat4& modelMatrix, const glm::vec3& brickColor) {
        m_shader.use();

        m_shader.setMatrixUniform("model", modelMatrix);
        glUniform3fv(m_shader.uniformLocation("brickColor"), 1, glm::value_ptr(brickColor));

        m_rect.draw();
    }

    Brick::Brick(const glm::vec3& worldPos, bool isDestroyable)
        : m_worldPos(worldPos)
        , m_isDestroyable(isDestroyable)
        , m_isDestroyed(false)
        , m_modelMatrix(glm::mat4(1.0f))
    {
        m_modelMatrix = glm::translate(glm::mat4(1.0f), m_worldPos);
    }

    void Brick::update(GameObject::Ball& ball) {
        if (Collision::circleRectangle(ball.circle().x(), 
                                       ball.circle().y(), 
                                       ball.circle().radius(), 
                                       m_worldPos.x, m_worldPos.y, 
                                       100.0f, 50.0f) && m_isDestroyable) {
            m_isDestroyed = true;
        }
    }
}

