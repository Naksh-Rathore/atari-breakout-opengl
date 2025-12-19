#include <vector>

#include <glad/glad.h>

#include <glm/glm.hpp>

#include "game_objects/brick.h"

namespace GameObject {
    BrickMesh::BrickMesh(const glm::vec3& pos)
        : m_rect(m_vertices, pos, m_indices, 8)
    {}

    void BrickMesh::linkShape() {
        m_rect.link();
        m_rect.linkAttrib(1, 3, 8 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
        m_rect.linkAttrib(2, 2, 8 * sizeof(GLfloat), (void *)(6 * sizeof(GLfloat)));
    }

    void BrickMesh::render() {
        m_rect.draw();
    }
}

