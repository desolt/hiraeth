#include "game.hpp"

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
    while (!m_win_ptr->should_close()) {
        glClearColor(0.3f, 0.3f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_win_ptr->update();
    }
}

} // namespace hiraeth
