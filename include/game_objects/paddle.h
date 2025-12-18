#ifndef PADDLE_H
#define PADDLE_H

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

namespace GameObject {
    class Paddle {
        private:
            Shape::Rectangle m_rect;
            Texture::Texture m_texture;

            Shader::Shader m_vert;
            Shader::Shader m_frag;

            Shader::ShaderProgram m_shader;
        
            float m_moveValue;

            bool isTouchingRightBorder(float posBorderX);
            bool isTouchingLeftBorder(float negBorderX);


        public:

            Paddle(const std::vector<GLfloat>& vertices,
                   const glm::vec3& pos,
                   const std::string& vertSourcePath,
                   const std::string& fragSourcePath,
                   float moveValue);

            Paddle(const Paddle&) = delete;            
            Paddle& operator=(const Paddle&) = delete;

            void linkShape();
            void linkShaders();
            void linkTextures(const std::string& texturePath);
            
            void render();
            void getKeyInput(GLFWwindow *window, float posBorderX, float negBorderX);

            Shape::Rectangle& rect() { return m_rect; }
            Texture::Texture& texture() { return m_texture; }
            Shader::Shader& vertShader() { return m_vert; }
            Shader::Shader& fragShader() { return m_frag; }
            Shader::ShaderProgram& shader() { return m_shader; }
            float moveValue() const { return m_moveValue; }
            
            // No setters for OpenGL managed lifetimes and objects
            void setMoveValue(float value) { m_moveValue = value; }
        
    };
}

#endif
