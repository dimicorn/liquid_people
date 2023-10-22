#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <random>
#include "node.hpp"

class LatticeGas {
private:
	const double cell_size = 50;
    const double c_width = 12, c_height = 12; // should be even numbers
    const double dl = 50;

    const double width = c_width * cell_size;
    const double height = c_height * cell_size * sqrt3_2;
	const unsigned int w_width = width + 2 * dl, w_height = height + 2 * dl;
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(w_width, w_height), 
    "Lattice Gas Cellular Automata");
	std::vector<Node> nodes;

    std::pair<UnitVector, int> randomVelocity(const int &i, const int &j);
	void initNodes();
    void drawNodes();
    void drawNode(const Node &n);
    int index(const int &i, const int &j);
    void updateNodes();
    bool check_ind(const int &i, const int &j);
    Node checkNeighbors(Node &n, const int &i, const int &j);
    void checkCollision(Node &n);
    void drawGrid();
	void drawTriangle(const int &i, const int &j);
	void drawRTriangle(const int &i, const int &j);
	void handleEvents();

public:
	LatticeGas();
	void run();
};
