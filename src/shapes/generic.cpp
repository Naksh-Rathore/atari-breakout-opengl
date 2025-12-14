#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shapes/generic.h"

#include <vector>

namespace Shape {
    GenericShape::GenericShape(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, int componentAmount, GLenum drawMode)
        : m_componentAmount { componentAmount }   
        , m_drawMode { drawMode }                 
        , m_VBO{}                                 
        , m_VAO{}
        , m_EBO{}
        , m_vertices { vertices }                 
        , m_indices { indices }                   
    {
    }

    GenericShape::~GenericShape() {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
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
        if (drawMode == 0)
            drawMode = m_drawMode;

        glBindVertexArray(m_VAO);

        if (m_indices.empty())
            glDrawArrays(drawMode, first, count);

        else
            glDrawElements(drawMode, count, GL_UNSIGNED_INT, 0);
    }


    void GenericShape::addVertex(GLfloat x, GLfloat y) {
        m_vertices.push_back(x);
        m_vertices.push_back(y);
        m_vertices.push_back(0.0f);
    }

    void GenericShape::removeLastVertex() {
        if (m_vertices.size() >= 3) {
            m_vertices.pop_back();
            m_vertices.pop_back();
            m_vertices.pop_back();
        }
    }


    void GenericShape::linkAttrib(int index, int size, int stride, void *offset) {
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(index);
    }

}
