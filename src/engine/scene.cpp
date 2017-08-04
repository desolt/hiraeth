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
        m_renderer = std::make_unique<sprite_renderer>(line, win);
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

            if (tokens.size() < 6)
                throw std::runtime_error("engine::scene: error parsing file " + path);

            float x = std::stof(tokens[0]);
            float y = std::stof(tokens[1]);
            float s1 = std::stof(tokens[2]);
            float t1 = std::stof(tokens[3]);
            float s2 = std::stof(tokens[4]);
            float t2 = std::stof(tokens[5]);

            m_props.push_back({{ x, y }, { s1, t1, s2, t2 }, prop_type::SOLID});
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