#ifndef CIRCLE_H
#define CIRCLE_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "generic.h"

namespace Shape {
    class Circle : public GenericShape {
        private:
            float m_radius{};
            int m_segments{};

        public:
            Circle(float radius = 0.0f, int segments = 0, const glm::vec3& pos = glm::vec3(0.0f, 0.0f, 0.0f), int componentAmount = 3);

            void generateVertices(float scale = 1.0f, bool genTextures = false);
            void draw(GLuint shaderID, bool passMVP = true);

            inline float radius() const { return m_radius; }
            inline void setRadius(float r) { m_radius = r; }

            inline int segments() const { return m_segments; }
            inline void setSegments(int s) { m_segments = s; }

    };
}


#endif
