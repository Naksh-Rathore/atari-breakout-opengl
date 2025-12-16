#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shapes/generic.h"

#include "shaders/shader_program.h"

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Shape {
    GenericShape::GenericShape(const std::vector<GLfloat>& vertices, 
                         const glm::vec3& pos,
                         const std::vector<GLuint>& indices,
                         int componentAmount, 
                         GLenum drawMode)     
        : m_vertices { vertices }
        , m_pos { pos }
        , m_indices { indices }
        , m_componentAmount { componentAmount }
        , m_drawMode { drawMode }    
        , m_modelMatrix { glm::translate(glm::mat4(1.0f), pos) }
    {
    }

    GenericShape::~GenericShape() {
        if (m_VAO) glDeleteVertexArrays(1, &m_VAO);
        if (m_VBO) glDeleteBuffers(1, &m_VBO);
        if (m_EBO) glDeleteBuffers(1, &m_EBO);
    }

    void GenericShape::link() {
        glGenVertexArrays(1, &m_VAO);  
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat), m_vertices.data(), GL_STATIC_DRAW);

        linkAttrib(0, 3, m_componentAmount * sizeof(GLfloat), (void *) 0);

        if (!m_indices.empty()) {
            glGenBuffers(1, &m_EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), m_indices.data(), GL_STATIC_DRAW);
        }
    }


    void GenericShape::draw(GLuint first, GLuint count, GLenum drawMode) {
        glBindVertexArray(m_VAO);

        if (m_indices.empty())
            glDrawArrays(drawMode, first, count);

        else
            glDrawElements(drawMode, count, GL_UNSIGNED_INT, 0);
    }


    void GenericShape::linkAttrib(int index, int size, int stride, void *offset) {
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(index);
    }

}
