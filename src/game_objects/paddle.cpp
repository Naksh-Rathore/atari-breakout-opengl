#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shapes/rectangle.h"
#include "textures/texture.h"
#include "shaders/shader.h"
#include "shaders/shader_program.h"

#include "game_objects/paddle.h"

#include <iostream>

namespace GameObject {
    Paddle::Paddle(const std::vector<GLfloat>& vertices,
                   const glm::vec3& pos,
                   const std::string& vertSourcePath,
                   const std::string& fragSourcePath,
                   float moveValue)
        : m_rect(vertices, pos, std::vector<GLuint>{0, 1, 3, 1, 2, 3}, 5)
        , m_vert(vertSourcePath, GL_VERTEX_SHADER)
        , m_frag(fragSourcePath, GL_FRAGMENT_SHADER)
        , m_moveValue(moveValue)
    {
    }

    bool Paddle::isTouchingRightBorder(float posBorderX) {
        if (m_rect.x() > posBorderX)
            return true;

        return false;
    }

    bool Paddle::isTouchingLeftBorder(float negBorderX) {
        if (m_rect.x() < negBorderX)
            return true;

        return false;
    }


    void Paddle::render() {
        m_shader.use();
        m_texture.use();

        m_shader.setMatrixUniform("model", m_rect.modelMatrix());

        m_rect.draw();
    }

    void Paddle::getKeyInput(GLFWwindow *window, float posBorderX, float negBorderX) {
        if (glfwGetKey(window, GLFW_KEY_RIGHT) && !isTouchingRightBorder(posBorderX))
            m_rect.translate(m_moveValue, 0.0f, 0.0f);
        if (glfwGetKey(window, GLFW_KEY_LEFT) && !isTouchingLeftBorder(negBorderX))
            m_rect.translate(-m_moveValue, 0.0f, 0.0f);
    }

    void Paddle::linkShape() {
        m_rect.link();
        m_rect.linkAttrib(1, 2,  5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    }

    void Paddle::linkShaders() {
        m_vert.compileShader();
        m_frag.compileShader();

        m_shader.link(m_vert, m_frag);
    }

    void Paddle::linkTextures(const std::string& texturePath) {
        m_texture.link(texturePath, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    }
}
