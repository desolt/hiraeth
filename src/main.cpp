#include "game.hpp"
#include <iostream>

int main()
{
    hiraeth::game &game = hiraeth::game::instance();
    try {
        game.loop();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}