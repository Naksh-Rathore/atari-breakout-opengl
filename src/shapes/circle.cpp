#define _USE_MATH_DEFINES
#include <cmath>

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shapes/circle.h"
#include "shapes/generic.h" 


namespace Shape {
    Circle::Circle(float radius, int segments, const glm::vec3& pos, int componentAmount)
        : GenericShape({}, pos, {}, componentAmount, GL_TRIANGLE_FAN)
        , m_radius { radius }
        , m_segments { segments }
    {
    }

    void Circle::generateVertices(float scale, bool genTextures) {
        if (!m_vertices.empty())
            return;

        for (int i = 0; i < 3; i++)
            m_vertices.push_back(0.0f);

        if (genTextures) {
            m_vertices.push_back(0.5f);
            m_vertices.push_back(0.5f);
        }   

        for (int i = 0; i <= m_segments; i++) {
            float theta = 2.0f * M_PI * i / m_segments;

            float x { (m_radius * cos(theta)) * scale };
            float y { (m_radius * sin(theta)) * scale };

            m_vertices.push_back(x);
            m_vertices.push_back(y);
            m_vertices.push_back(0.0f);

            if (genTextures) {
                float s { 0.5f + (cos(theta) * 0.5f) };
                float t { 0.5f + (sin(theta) * 0.5f) };

                m_vertices.push_back(s);
                m_vertices.push_back(t);
            }
        }
    }

    void Circle::draw(GLuint shaderID, bool passMVP) {
        glUseProgram(shaderID);

        if (passMVP)
            glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, glm::value_ptr(this->modelMatrix()));

        glBindVertexArray(this->VAO());
        glDrawArrays(drawMode(), 0, m_segments + 2);
    }
}
