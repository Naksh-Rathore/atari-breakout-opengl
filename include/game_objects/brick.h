#ifndef BRICK_H
#define BRICK_H

#include <vector>

#include <glad/glad.h>

#include <glm/glm.hpp>

#include "shapes/rectangle.h"

namespace GameObject {
    class BrickMesh {
        private:
            std::vector<GLfloat> m_vertices {
                // pos               // tex
                0.5f,  0.25f, 0.0f,  1.0f, 1.0f,
                0.5f, -0.25f, 0.0f,  1.0f, 0.0f,
                -0.5f, -0.25f, 0.0f, 0.0f, 0.0f,
                -0.5f,  0.25f, 0.0f, 0.0f, 1.0f
            };
        
            std::vector<GLuint> m_indices {
                0, 1, 3,
                1, 2, 3
            };

            Shape::Rectangle m_rect;

        public:
            explicit BrickMesh(const glm::vec3& pos);  

            void linkShape();
            void render();
            
            BrickMesh(const BrickMesh&) = delete;            
            BrickMesh& operator=(const BrickMesh&) = delete;

            std::vector<GLfloat>& vertices() { return m_vertices; }
            std::vector<GLuint>& indices() { return m_indices; }
            Shape::Rectangle& rect() { return m_rect; }
    };

    class Brick {
        
    };
}

#endif
