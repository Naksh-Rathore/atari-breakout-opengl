#include "shapes/rectangle.h"

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Shape {
    Rectangle::Rectangle(const std::vector<GLfloat>& vertices, const glm::vec3& pos, const std::vector<GLuint>& indices, int componentAmount) 
        : GenericShape(vertices, pos, indices, componentAmount)
    {
    }

    void Rectangle::draw() {
        glBindVertexArray(this->VAO());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

}
