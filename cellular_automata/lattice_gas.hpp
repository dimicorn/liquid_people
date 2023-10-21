#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <random>

const double sqrt3_2 = sqrt(3) / 2;
const double sqrt3 = sqrt(3);

struct UnitVector {
	double x, y;

    bool operator==(const UnitVector &v) const {
        return (x == v.x && y == v.y);
    }
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
	const double cell_size = 50;
    const double c_width = 12, c_height = 12;
    const double dl = 50;

    const double width = c_width * cell_size;
    const double height = c_width * cell_size * sqrt3_2;
	const unsigned int w_width = width + 2 * dl, w_height = height + 2 * dl;
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(w_width, w_height), 
    "Lattice Gas Cellular Automata");
	std::vector<Node> nodes;

    std::pair<UnitVector, bool> randomVelocity(const int &i, const int &j);
	void initNodes();
    void drawNodes();
    void drawNode(const Node &n);
    int index(const int &i, const int &j);
    void updateNodes();
    void drawGrid();
	void drawTriangle(const int &i, const int &j);
	void drawRTriangle(const int &i, const int &j);
	void drawBox();
	void handleEvents();

public:
	LatticeGas();
	void run();
};
