#ifndef GAME_OF_LIFE_HPP
#define GAME_OF_LIFE_HPP

#include <SFML/Graphics.hpp>

const bool alive = true;
const bool dead = false;

class GameOfLife {
private:
	const unsigned int cell_size;
	const unsigned int w_width, w_height;
	const float dl, width, height;
	const float c_width, c_height;
    sf::RenderWindow window;
	std::vector<bool> cells;

	void initCells();
	bool checkNeighbors(bool c, const int i, const int j);
	void updateCells();
	void drawBox();
	void drawCell(bool c, const float x, const float y);
	void drawCells();
	void handleEvents();

	int index(const int i, const int j);
	bool check_ind(const int i, const int j);
public:
	GameOfLife();
	void run();
};

#endif
