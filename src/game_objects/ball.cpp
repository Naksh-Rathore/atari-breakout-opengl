#include "game_objects/ball.h"
#include "game_objects/paddle.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include <string>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shapes/circle.h"

#include "textures/texture.h"

#include "shaders/shader.h"
#include "shaders/shader_program.h"

namespace GameObject {
    Ball::Ball(float radius,
                 int segments,
                 const glm::vec3& pos,
                 const std::string& vertSourcePath,
                 const std::string& fragSourcePath,
                 const glm::vec3& velocity)
        : m_circle(radius, segments, pos, 5)
        , m_vert(vertSourcePath, GL_VERTEX_SHADER)
        , m_frag(fragSourcePath, GL_FRAGMENT_SHADER)
        , m_velocity(velocity)
    {
    }

    void Ball::linkShape() {
        m_circle.link();
        m_circle.linkAttrib(1, 2,  5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    }

    void Ball::linkShaders() {
        m_vert.compileShader();
        m_frag.compileShader();

        m_shader.link(m_vert, m_frag);
    }

    void Ball::render() {
        m_shader.use();
        m_texture.use();

        m_shader.setMatrixUniform("model", m_circle.modelMatrix());

        m_circle.draw();
    }
    
    void Ball::linkTextures(const std::string& texturePath) {
        m_texture.link(texturePath, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    }

    bool Ball::isTouchingPaddle(Paddle& paddle, float paddleWidth, float paddleHeight) {
        float circleDistanceX { abs(m_circle.x() - paddle.rect().x()) };
        float circleDistanceY { abs(m_circle.y() - paddle.rect().y()) };

        if (circleDistanceX > (paddleWidth / 2 + m_circle.radius())) { return false; }
        if (circleDistanceY > (paddleHeight / 2 + m_circle.radius())) { return false; }
    
        if (circleDistanceX <= (paddleWidth / 2)) { return true; } 
        if (circleDistanceY <= (paddleHeight / 2)) { return true; }

        float cornerDistanceSquared { pow((circleDistanceX - paddleWidth/2), 2) + pow((circleDistanceY - paddleHeight/2), 2) };
    
        return (cornerDistanceSquared <= pow(m_circle.radius(), 2));
    }

    void Ball::update(Paddle& paddle, float paddleWidth, float paddleHeight) {

        if (isTouchingPaddle(paddle, paddleWidth, paddleHeight))
            m_velocity.y *= -1;

        if (m_circle.x() > 350.0f || m_circle.x() < -350.0f)
            m_velocity.x *= -1;
        if (m_circle.y() > 350.0f || m_circle.y() < -350.0f)
            m_velocity.y *= -1;

        m_circle.translate(m_velocity);
    }
}

