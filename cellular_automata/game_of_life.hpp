#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>

const bool alive = true;
const bool dead = false;

class GameOfLife {
private:
	const unsigned int cell_size = 5;
	const unsigned int w_width = 600, w_height = 600;
	const float dl = 50;
    const float width = w_width - 2 * dl;
    const float height = w_height - 2 * dl;
	const float c_width = width / cell_size, c_height = height / cell_size;
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(w_width, w_height), "Game of Life");
	std::vector<bool> cells;

	void initCells();
	bool checkNeighbors(const bool &c, const int &i, const int &j);
	void updateCells();
	void drawBox();
	void drawCell(const bool &c, const float &x, const float &y);
	void drawCells();
	void handleEvents();

	int index(const int &i, const int &j);
	bool check_ind(const int &i, const int &j);

public:
	GameOfLife();
	void run();
};
