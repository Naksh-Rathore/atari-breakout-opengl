#ifndef GENERIC_H
#define GENERIC_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaders/shader_program.h"

namespace Shape {
    class GenericShape {
        protected:
            std::vector<GLfloat> m_vertices{};

        private:
            glm::vec3 m_pos{};
            std::vector<GLuint> m_indices{};
            int m_componentAmount{};
            GLenum m_drawMode{};

            GLuint m_VBO{};
            GLuint m_VAO{};
            GLuint m_EBO{};

            glm::mat4 m_modelMatrix{};

        public:
            GenericShape(const std::vector<GLfloat>& vertices = {}, 
                         const glm::vec3& pos = glm::vec3(0.0f, 0.0f, 0.0f),
                         const std::vector<GLuint>& indices = {},
                         int componentAmount = 3, 
                         GLenum drawMode = GL_TRIANGLES);    

            GenericShape(const GenericShape&) = delete;            
            GenericShape& operator=(const GenericShape&) = delete;

            virtual ~GenericShape();

            void link();
            void linkAttrib(int index, int size, int stride, void *offset);

            void draw(GLuint first, GLuint count, GLenum drawMode);

            inline std::vector<GLfloat> vertices() const { return m_vertices; }
            inline void setVertices(const std::vector<GLfloat>& v) { m_vertices = v; }

            inline std::vector<GLuint> indices() const { return m_indices; }
            inline void setIndices(const std::vector<GLuint>& i) { m_indices = i; }

            inline GLenum drawMode() const { return m_drawMode; }
            inline void setdrawMode(GLenum d) { m_drawMode = d; }

            inline GLuint VBO() const { return m_VBO; }
            inline GLuint VAO() const { return m_VAO; }
            inline GLuint EBO() const { return m_EBO; }

            const glm::mat4& modelMatrix() { return m_modelMatrix; }
            void setModelMatrix(glm::mat4& m) { 
                m_modelMatrix = m;
                m_pos = glm::vec3(m[3]);
            }

            const glm::vec3& pos() const { return m_pos; }
            void setPos(const glm::vec3& pos) {
                m_pos = pos; 
                m_modelMatrix = glm::translate(glm::mat4(1.0f), m_pos);
            }

            void translate(float x, float y, float z) { 
                m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(x, y, z)); 
                m_pos += glm::vec3(x, y, z);
            }
            
            void translate(const glm::vec3& transformationMatrix) { 
                m_modelMatrix = glm::translate(m_modelMatrix, transformationMatrix); 
                m_pos += transformationMatrix;
            }
            
            void resetModelMatrix() { m_modelMatrix = glm::mat4(1.0f); }

            int x() { return m_pos.x; }
            int y() { return m_pos.y; }
            int z() { return m_pos.z; }
    };
}

#endif
