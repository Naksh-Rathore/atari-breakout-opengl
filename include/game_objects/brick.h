#ifndef BRICK_H
#define BRICK_H

#include <vector>

#include <glad/glad.h>

#include <glm/glm.hpp>

#include "shapes/rectangle.h"

#include "game_objects/ball.h"

namespace GameObject {
    class BrickMesh {
        private:
            std::vector<GLfloat> m_vertices {
                // pos               
                50.0f,  25.0f, 0.0f, 
                50.0f, -25.0f, 0.0f,  
                -50.0f, -25.0f, 0.0f, 
                -50.0f,  25.0f, 0.0f, 
            };
        
            std::vector<GLuint> m_indices {
                0, 1, 3,
                1, 2, 3
            };

            Shape::Rectangle m_rect;
            
            Shader::Shader m_vert;
            Shader::Shader m_frag;

            Shader::ShaderProgram m_shader;

        public:
            explicit BrickMesh(const glm::vec3& pos);  

            void linkShader();
            void render(const glm::mat4& modelMatrix, const glm::vec3& brickColor);
            
            BrickMesh(const BrickMesh&) = delete;            
            BrickMesh& operator=(const BrickMesh&) = delete;

            std::vector<GLfloat>& vertices() { return m_vertices; }
            std::vector<GLuint>& indices() { return m_indices; }
            Shape::Rectangle& rect() { return m_rect; }
            Shader::ShaderProgram& shader() { return m_shader; }
    };

    class Brick {
        private:    
            bool m_isDestroyable;
            bool m_isDestroyed { false };

            glm::mat4 m_modelMatrix;
            glm::vec3 m_worldPos;

        public:
            Brick(const glm::vec3& worldPos, bool isDestroyable = true);

            void update(GameObject::Ball& ball);

            bool isDestroyable() const { return m_isDestroyable; }
            void setIsDestroyable(bool value) { m_isDestroyable = value; }

            bool isDestroyed() const { return m_isDestroyed; }
            void setIsDestroyed(bool value) { m_isDestroyed = value; }

            const glm::mat4& modelMatrix() const { return m_modelMatrix; }
            void setModelMatrix(const glm::mat4& matrix) { m_modelMatrix = matrix; }

            const glm::vec3& worldPos() const { return m_worldPos; }
            void setWorldPos(const glm::vec3& pos) { m_worldPos = pos; }
    };
}

#endif
