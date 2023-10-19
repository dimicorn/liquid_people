#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>

const double sqrt3_2 = sqrt(3) / 2;

struct UnitVector {
	double x, y;
};

const UnitVector zero = {0, 0};
const UnitVector left = {-1, 0};
const UnitVector right = {1, 0};
const UnitVector top_left = {-0.5, sqrt3_2};
const UnitVector top_right = {0.5, -sqrt3_2};
const UnitVector bottom_left = {-0.5, sqrt3_2};
const UnitVector bottom_right = {0.5, sqrt3_2};

struct Node {
	UnitVector velocity;
	double x, y;
	bool isEmpty, isWall;
};

class LatticeGas {
private:
	const double cell_size = 100;
	const unsigned int w_width = 600, w_height = 600;
    const double dl = 50;
    const double width = w_width - 2 * dl;
    const double height = w_height - 2 * dl;
    const double c_width = width / cell_size, c_height = height / (cell_size * sqrt3_2);
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(w_width, w_height), 
    "Lattice Gas Cellular Automata");
	std::vector<Node> nodes;

	void initNodes();
	void drawTriangle();
	void drawRTriangle();
	void drawBox();
	void handleEvents();

public:
	LatticeGas();
	void run();
};
