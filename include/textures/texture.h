#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Texture {
    class Texture {
        private:
            GLuint m_texture{};

        public:
            void link(const std::string& fileName, GLenum wrapOption, GLenum mipMapMinOption, GLenum mipMapMagOption);
            void use(GLuint unit = 0);

            ~Texture();

            GLuint texture() { return m_texture; }
            void setTexture(GLuint t) { m_texture = t; }
    };
}

#endif
