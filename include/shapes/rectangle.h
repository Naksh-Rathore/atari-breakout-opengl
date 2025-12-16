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
            Rectangle(const std::vector<GLfloat>& vertices, const glm::vec3& pos, const std::vector<GLuint>& indices, int componentAmount);

            void draw();
    };
}

#endif
