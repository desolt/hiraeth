#include "engine/scene.hpp"
#include <fstream>

namespace hiraeth::engine {

    scene::scene(const std::string &path, window &win, std::shared_ptr<camera> cam_ptr)
    {
        std::ifstream file(path);
        if (!file.is_open())
            throw std::runtime_error("engine::scene: could not locate scene file " + path);

        std::string line; // first line should be path to texture atlas
        std::getline(file, line);
        m_renderer = std::make_unique<sprite_renderer>(line, glm::vec2{64.0f}, win);
        m_renderer->set_camera(cam_ptr);

        while (std::getline(file, line)) {
            std::vector<std::string> tokens;
            const char *ptr = line.c_str();

            do {
                const char *begin = ptr;
                while (*ptr != ' ' && *ptr != '\0')
                    ++ptr;
                tokens.push_back(std::string(begin, ptr));
            } while (*ptr != '\0' && *(++ptr) != '\0');

            if (tokens.size() < 4)
                throw std::runtime_error("engine::scene: error parsing file " + path);

            float x = std::stof(tokens[0]) * 64.0f;
            float y = std::stof(tokens[1]) * 64.0f;
            float s = std::stof(tokens[2]) * 64.0f;
            float t = std::stof(tokens[3]) * 64.0f;

            m_props.push_back({{ x, y }, { s, t }, prop_type::SOLID});
        }
    }

    void scene::draw()
    {
        for (auto &prop: m_props) {
            m_renderer->draw_sprite({ prop.pos, 0.0f }, prop.sprite);
        }

        m_renderer->render();
    }

}