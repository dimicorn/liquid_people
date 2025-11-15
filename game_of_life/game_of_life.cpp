#include "game_of_life.hpp"

GameOfLife::GameOfLife() {
	initCells();
}

void GameOfLife::run() {
	sf::Time t = sf::milliseconds(500);
	while(window.isOpen()) {
		window.clear();
		drawCells();
		updateCells();
		drawBox();
		window.display();
		handleEvents();
		sf::sleep(t);
	}
}

void GameOfLife::initCells() {
	for (int i = 0; i < c_height; ++i) {
		for (int j = 0; j < c_width; ++j) {
			bool c;
			if (rand() % 2 == 0) {
				c = alive;
			} else {
				c = dead;
			}
			cells.push_back(c);
		}
	}
}
	
void GameOfLife::drawBox() {
	sf::Vertex bottom[] = {
		sf::Vertex(sf::Vector2f(dl, height + dl), sf::Color::Red),
		sf::Vertex(sf::Vector2f(width + dl, height + dl), sf::Color::Red)
	};
	sf::Vertex top[] = {
		sf::Vertex(sf::Vector2f(dl, dl), sf::Color::Red),
		sf::Vertex(sf::Vector2f(width + dl, dl), sf::Color::Red)
	};
	sf::Vertex left[] = {
		sf::Vertex(sf::Vector2f(dl, dl), sf::Color::Red),
		sf::Vertex(sf::Vector2f(dl, height + dl), sf::Color::Red)
	};
	sf::Vertex right[] = {
		sf::Vertex(sf::Vector2f(width + dl, dl), sf::Color::Red),
		sf::Vertex(sf::Vector2f(width + dl, height + dl), sf::Color::Red)
	};
			
	window.draw(bottom, 3, sf::Lines);
	window.draw(top, 2, sf::Lines);
	window.draw(left, 2, sf::Lines);
	window.draw(right, 2, sf::Lines);
}

void GameOfLife::drawCell(const bool &c, const float &x, const float &y) {
	sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));
	cell.setPosition(x, y);
	if (c == alive) {
		cell.setFillColor(sf::Color::Green);
	} else if (c == dead) {
		cell.setFillColor(sf::Color::Black);
	}
	window.draw(cell);
}

void GameOfLife::drawCells() {
	for (int i = 0; i < c_height; ++i) {
		for (int j = 0; j < c_width; ++j) {
			drawCell(cells[index(i, j)], dl + j * cell_size, dl + i * cell_size);
		}
	}
}

int GameOfLife::index(const int &i, const int &j) {
	return i * c_height + j;
}

bool GameOfLife::check_ind(const int &i, const int &j) {
	if (0 <= i && i < c_height && 0 <= j && j < c_width) {
		return true;
	}
	return false;
}

bool GameOfLife::checkNeighbors(const bool &c, const int &i, const int &j) {
	int alive_neighbors = 0;
	// top neighbor
	if (check_ind(i-1, j) && cells[index(i-1, j)] == alive) {
		++alive_neighbors;
	}
	// bottom neighbor
	if (check_ind(i+1, j) && cells[index(i+1, j)] == alive) {
		++alive_neighbors;
	}
	// right neighbor
	if (check_ind(i, j+1) && cells[index(i, j+1)] == alive) {
		++alive_neighbors;
	}
	// left neighbor
	if (check_ind(i, j-1) && cells[index(i, j-1)] == alive) {
		++alive_neighbors;
	}
	// bottom right neighbor
	if (check_ind(i-1, j+1) && cells[index(i-1, j+1)] == alive) {
		++alive_neighbors;
	}
	// top right neighbor
	if (check_ind(i+1, j+1) && cells[index(i+1, j+1)] == alive) {
		++alive_neighbors;
	}
	// top left neighbor
	if (check_ind(i+1, j-1) && cells[index(i+1, j-1)] == alive) {
		++alive_neighbors;
	}
	// bottom left neighbor
	if (check_ind(i-1, j-1) && cells[index(i-1, j-1)] == alive) {
		++alive_neighbors;
	}

	if (c == alive && alive_neighbors < 2) {
		return dead;
	} else if (c == alive && (alive_neighbors == 2 || alive_neighbors == 3)) {
		return alive;
	} else if (c == alive && alive_neighbors > 3) {
		return dead;
	} else if (c == dead && alive_neighbors == 3) {
		return alive;
	} else {
		return dead;
	}
}

void GameOfLife::updateCells() {
	std::vector<bool> upd;
	for (int i = 0; i < c_height; ++i) {
		for (int j = 0; j < c_width; ++j) {
			upd.push_back(checkNeighbors(cells[index(i, j)], i, j));
		}
	}
	cells = upd;
}

void GameOfLife::handleEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
	}
}
