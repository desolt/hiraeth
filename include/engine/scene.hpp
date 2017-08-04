#ifndef HIRAETH_ENGINE_SCENE_HPP
#define HIRAETH_ENGINE_SCENE_HPP

#include "engine/sprite_renderer.hpp"
#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace hiraeth::engine {

    enum class prop_type {
        SOLID = 0,
        AIR = 1,
    };

    struct prop {
        glm::vec2 pos;
        glm::vec2 sprite;

        prop_type type;
    };

    class scene {
    public:
        scene(const std::string &path, window &win, std::shared_ptr<camera> cam_ptr);

        void draw();

    private:
        std::vector<prop> m_props;

        std::unique_ptr<sprite_renderer> m_renderer;
    };

} // namespace hiraeth::engine

#endif // HIRAETH_ENGINE_SCENE_HPP
