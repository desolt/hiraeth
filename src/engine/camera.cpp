#include "engine/camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace hiraeth::engine {

    camera::camera()
            : m_pos(0.0f)
    {
    }

    camera::~camera()
    {
    }

    void camera::set_pos(const glm::vec2 &pos)
    {
        m_pos = pos;
    }

    glm::vec2 &camera::get_pos()
    {
        return m_pos;
    }

    const glm::vec2 &camera::get_pos() const
    {
        return m_pos;
    }

    glm::mat4 camera::view_matrix()
    {
        glm::mat4 matrix;
        matrix = glm::translate(matrix, glm::vec3(m_pos, 0.0f));
        return matrix;
    }

} // namespace hiraeth::engine
