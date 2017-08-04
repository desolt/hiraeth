#include "engine/sprite_renderer.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace hiraeth::engine {

    sprite_renderer::sprite_renderer(const std::string &sprite_sheet_path, const glm::vec2 &tile_dimensions, window &win)
            : m_program("/home/shawn/projects/hiraeth/res/shaders/vertex.glsl", "/home/shawn/projects/hiraeth/res/shaders/fragment.glsl"), // TODO: Get from some sort of manager that finds path.
              m_texture(sprite_sheet_path),
              m_tile_dimensions(tile_dimensions)
    {
        // matrix setup
        auto set_projection = [this](int width, int height) {
            m_projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
        };
        win.on_resize(static_cast<std::function<void (int, int)>>(set_projection));
        set_projection(win.get_width(), win.get_height());

        m_vertices.reserve(4096);

        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ARRAY_BUFFER, 4096 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    sprite_renderer::~sprite_renderer()
    {
        glDeleteBuffers(1, &m_vbo);
        glDeleteVertexArrays(1, &m_vao);
    }

    void sprite_renderer::set_camera(std::shared_ptr<camera> camera)
    {
        m_camera_ptr = camera;
    }

    void sprite_renderer::draw_sprite(const glm::vec3 &pos, const glm::vec2 &tile)
    {
        // TODO: Ignore sprites that aren't visible.

        float x1 = pos.x;
        float y1 = pos.y;
        float x2 = pos.x + m_tile_dimensions.x;
        float y2 = pos.y + m_tile_dimensions.y;
        float z = pos.z;

        float s1 = (tile.x * m_tile_dimensions.x) / m_texture.get_width();
        float t1 = (tile.y * m_tile_dimensions.y) / m_texture.get_height();
        float s2 = ((tile.x * m_tile_dimensions.x) + m_tile_dimensions.x) / m_texture.get_width();
        float t2 = ((tile.y * m_tile_dimensions.y) + m_tile_dimensions.y) / m_texture.get_height();

        m_vertices.insert(m_vertices.end(), { x1, y1, z, s1, t1 });
        m_vertices.insert(m_vertices.end(), { x2, y1, z, s2, t1 });
        m_vertices.insert(m_vertices.end(), { x1, y2, z, s1, t2 });
        m_vertices.insert(m_vertices.end(), { x1, y2, z, s1, t2 });
        m_vertices.insert(m_vertices.end(), { x2, y1, z, s2, t1 });
        m_vertices.insert(m_vertices.end(), { x2, y2, z, s2, t2 });

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferSubData(GL_ARRAY_BUFFER, (m_vertex_count * 5) * sizeof(float), 30 * sizeof(float), &m_vertices[m_vertex_count * 5]);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        m_vertex_count += 6;
    }

    void sprite_renderer::render()
    {
        m_program.use();
        m_program.set_mat4("projection", m_projection);
        if (m_camera_ptr != nullptr)
            m_program.set_mat4("view", m_camera_ptr->view_matrix());
        else
            m_program.set_mat4("view", glm::mat4());
        m_texture.bind();
        glBindVertexArray(m_vao);
            glDrawArrays(GL_TRIANGLES, 0, m_vertex_count);
        glBindVertexArray(0);

        m_vertices.erase(m_vertices.begin(), m_vertices.end());
        m_vertex_count = 0;
    }

} // namespace hiraeth::engine
