#include "game.hpp"
#include "engine/scene.hpp"
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
        m_cam_ptr = std::make_shared<engine::camera>();

        m_win_ptr->on_key([this](int key, int, int, int action) {
            switch (key) {
                case GLFW_KEY_RIGHT:
                    m_cam_ptr->get_pos().x -= 5.0f;
                    break;
                case GLFW_KEY_LEFT:
                    m_cam_ptr->get_pos().x += 5.0f;
            }
        });
    }

    game::~game()
    {
        glfwTerminate();
    }

    void game::loop()
    {
        m_win_ptr->on_resize([](int width, int height) {
            std::cout << width << " " << height << std::endl;
        });

        /*
        engine::sprite_renderer renderer("/home/shawn/projects/hiraeth/res/textures/CharsetRed1.png", { 64.0f, 64.0f }, *m_win_ptr);
        renderer.set_camera(m_cam_ptr);
         */
        engine::scene scene("/home/shawn/projects/hiraeth/res/scenes/demo.scene", *m_win_ptr, m_cam_ptr);

        while (!m_win_ptr->should_close()) {
            glClearColor(0.3f, 0.3f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            scene.draw();

            /*
            renderer.draw_sprite({ glfwGetTime() * 100 , 256.0f, 0.0f }, { static_cast<float>(static_cast<int>(glfwGetTime()) % 4), 1.0f });
            renderer.render();
             */

            m_win_ptr->update();
        }
    }

} // namespace hiraeth
