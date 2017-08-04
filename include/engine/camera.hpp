#ifndef HIRAETH_ENGINE_CAMERA_HPP
#define HIRAETH_ENGINE_CAMERA_HPP

#include <glm/glm.hpp>

namespace hiraeth::engine {

    class camera {
    public:
        camera();
        ~camera();

        void set_pos(const glm::vec2 &pos);
        glm::vec2 &get_pos();
        const glm::vec2 &get_pos() const;

        glm::mat4 view_matrix();

    private:
        glm::vec2 m_pos;
    };

} // namespace hiraeth::engine

#endif //HIRAETH_ENGINE_CAMERA_HPP
