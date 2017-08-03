#include "game.hpp"
#include "engine/sprite_renderer.hpp"
#include <iostream>

namespace hiraeth {

game& game::instance()
{
    static game game;
    return game;
}

game::game()
{
    glfwInit();

    m_win_ptr = std::make_unique<engine::window>("hiraeth", 800, 600);
}

game::~game()
{
    glfwTerminate();
}

void game::loop()
{
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0, 0.0,
             0.5f, -0.5f, 0.0f, 1.0, 0.0,
             0.0f,  0.5f, 0.0f, 0.5, 1.0,

             0.9f,  0.9f, 1.0f, 1.0f, 1.0f,
             0.4f,  0.9f, 1.0f, 0.0f, 1.0f,
             0.7f,  0.4f, 1.0f, 0.5f, 0.0f,

            -1.0f, -1.0f, 1.0f, 0.0f, 0.25f,
            -0.8f, -1.0f, 1.0f, 0.25f, 0.25f,
            -1.0f, -0.8f, 1.0f, 0.0f, 0.0f,
            -0.8f, -1.0f, 1.0f, 0.25f, 0.25f,
            -1.0f, -0.8f, 1.0f, 0.0f, 0.0f,
            -0.8f, -0.8f, 1.0f, 0.25f, 0.0f,
    };

    m_win_ptr->on_resize([](int width, int height) {
        std::cout << width << " " << height << std::endl;
    });

    engine::sprite_renderer renderer("/home/shawn/projects/hiraeth/res/textures/CharsetRed1.png", { 64.0f, 64.0f }, *m_win_ptr);

    while (!m_win_ptr->should_close()) {
        glClearColor(0.3f, 0.3f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.draw_sprite({ 256.0f, 256.0f, 0.0f }, { static_cast<float>(static_cast<int>(glfwGetTime()) % 4), 1.0f });
        renderer.render();

        m_win_ptr->update();
    }
}

} // namespace hiraeth
