#ifndef HIRAETH_ENGINE_SPRITE_RENDERER_HPP
#define HIRAETH_ENGINE_SPRITE_RENDERER_HPP

#include "engine/camera.hpp"
#include "engine/window.hpp"
#include "gl/shader_program.hpp"
#include "gl/texture.hpp"
#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace hiraeth::engine {

    class sprite_renderer {
    public:
        sprite_renderer(const std::string &sprite_sheet_path, window &win);
        ~sprite_renderer();

        void set_camera(std::shared_ptr<camera> camera);

        void draw_sprite(const glm::vec3 &pos, const glm::vec4 &tile);
        void render();

    private:
        GLuint m_vao, m_vbo;
        std::vector<float> m_vertices;
        std::size_t m_vertex_count = 0;

        gl::shader_program m_program;
        gl::texture m_texture;

        glm::mat4 m_projection;
        std::shared_ptr<camera> m_camera_ptr;

        int m_screen_width = 0, m_screen_height = 0;

        glm::vec2 get_tile_pos(std::size_t tile) const;
    };

} // namespace hiraeth::engine

#endif //HIRAETH_ENGINE_SPRITE_RENDERER_HPP
