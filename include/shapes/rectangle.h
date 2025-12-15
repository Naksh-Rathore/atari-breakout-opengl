#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shapes/generic.h"

namespace Shape {
    class Rectangle : public GenericShape {
        public:
            Rectangle(std::vector<GLfloat>& vertices, glm::vec3& pos, std::vector<GLuint> indices, int componentAmount);

            void draw(GLuint shaderID = 0, bool passMVP = true);
    };
}

#endif
