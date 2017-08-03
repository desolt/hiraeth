#ifndef HIRAETH_ENGINE_SPRITE_RENDERER_HPP
#define HIRAETH_ENGINE_SPRITE_RENDERER_HPP

#include "engine/window.hpp"
#include "gl/shader_program.hpp"
#include "gl/texture.hpp"
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace hiraeth::engine {

    class sprite_renderer {
    public:
        sprite_renderer(const std::string &sprite_sheet_path, const glm::vec2 &tile_dimensions, window &win);
        ~sprite_renderer();

        void draw_sprite(const glm::vec3 &pos, const glm::vec2 &tile);
        void render();

    private:
        GLuint m_vao, m_vbo;
        std::vector<float> m_vertices;
        std::size_t m_vertex_count = 0;

        gl::shader_program m_program;
        gl::texture m_texture;
        glm::vec2 m_tile_dimensions;

        glm::mat4 m_projection;

        glm::vec2 get_tile_pos(std::size_t tile) const;
    };

} // namespace hiraeth::engine

#endif //HIRAETH_ENGINE_SPRITE_RENDERER_HPP
