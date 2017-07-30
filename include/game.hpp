#ifndef GAME_HPP_
#define GAME_HPP_

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

	std::unique_ptr<engine::window> m_window_ptr;

	// disallow copying
	game(const game &) {}
	game(game &&) {}
	void operator=(const game &) {}
	void operator=(game &&) {}
};

} // namespace hiraeth

#endif // GAME_HPP_
