#include "shapes/rectangle.h"

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Shape {
    Rectangle::Rectangle(std::vector<GLfloat>& vertices, glm::vec3& pos, std::vector<GLuint> indices, int componentAmount) 
        : GenericShape(vertices, pos, indices, componentAmount)
    {
    }

    void Rectangle::draw(GLuint shaderID, bool passMVP) {
        glUseProgram(shaderID);

        if (passMVP)
            glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, glm::value_ptr(this->modelMatrix()));

        glBindVertexArray(this->VAO());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

}
