#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaders/shader.h"

namespace Shader {
    class ShaderProgram {
        private:
            GLuint m_shaderProgram{};

        public:
            ShaderProgram();
            ~ShaderProgram();

            void link(Shader& vertexShader, Shader& fragmentShader);
            void use();

            GLuint uniformLocation(GLchar *uniformName);

            void setMatrixUniform(GLchar *uniformName, glm::mat4 matrix);

            GLuint shaderProgram() const { return m_shaderProgram; }
            void setShaderProgram(GLuint val) { m_shaderProgram = val; }

    };
}


#endif
