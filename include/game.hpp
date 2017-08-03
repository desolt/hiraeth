#ifndef HIRAETH_GAME_HPP
#define HIRAETH_GAME_HPP

#include "engine/window.hpp"
#include <memory>

namespace hiraeth {

    class game {
    public:
        static game &instance();
        ~game();

        void loop();

    private:
        game();

        std::unique_ptr<engine::window> m_win_ptr;

        game(const game &) {}
        game(game &&) {}
        void operator=(const game &) {}
        void operator=(game &&) {}
    };

} // namespace hiraeth


#endif //HIRAETH_GAME_HPP
