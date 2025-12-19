#ifndef BALL_H
#define BALL_H

#include <string>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shapes/circle.h"

#include "textures/texture.h"

#include "shaders/shader.h"
#include "shaders/shader_program.h"

#include "paddle.h"

namespace GameObject {
    class Ball {
        private:
            Shape::Circle m_circle;
            Texture::Texture m_texture;
            
            Shader::Shader m_vert;
            Shader::Shader m_frag;

            Shader::ShaderProgram m_shader;

            glm::vec3 m_velocity;

        public:
            Ball(float radius,
                 int segments,
                 const glm::vec3& pos,
                 const std::string& vertSourcePath,
                 const std::string& fragSourcePath,
                 const glm::vec3& velocity);

            void linkShape();
            void linkShaders();
            void linkTextures(const std::string& texturePath);

            void render();
            void update(Paddle& paddle, float paddleWidth, float paddleHeight);

            Ball(const Ball&) = delete;            
            Ball& operator=(const Ball&) = delete;

            Shape::Circle& circle() { return m_circle; }
            Texture::Texture& texture() { return m_texture; }
            Shader::Shader& vertShader() { return m_vert; }
            Shader::Shader& fragShader() { return m_frag; }
            Shader::ShaderProgram& shader() { return m_shader; }
    };
}

#endif
