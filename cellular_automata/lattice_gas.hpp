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
	void initNodes(const int &N);
    void drawNode(const Node &n);
    void updateNodes();
    bool check_ind(const int &i, const int &j);
    Node checkNeighbors(Node &n, const int &i, const int &j);
    void checkCollision(Node &n, const int &i, const int &j);
	void drawTriangle(const int &i, const int &j);
	void drawRTriangle(const int &i, const int &j);

    void drawNodes() {
        for (const auto &n : nodes) {
            drawNode(n);
        }
    }

    int index(const int &i, const int &j) {
        return j * (c_height + 1) + i + j / 2;
    }

    void drawGrid() {
        for (int j = 0; j < c_width / 2; ++j) {
            for (int i = 0; i < 2 * c_height + 1; ++i) {
                drawTriangle(i, j);
                drawRTriangle(i, j);
            }
        }
    }

	void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

public:
	LatticeGas(const int &N) {
        initNodes(N);
        int count = 0;
        for (const auto &n : nodes) {
            count += n.particleCount;
        }
        std::cout << "Number of particles: " << count << '\n';
        std::cout << "Number of nodes: " << nodes.size() << '\n';
        std::cout << "Density of particles: " << static_cast<double>(count) / nodes.size() << '\n';
    }
    
	void run() {
        sf::Time t = sf::milliseconds(100);
        // int count = 0;
        while(window.isOpen()) {
            window.clear();

            drawGrid();
            drawNodes();
            // if (count < 7) {
                updateNodes();
                // ++count;
            // }
            window.display();
            handleEvents();
            sf::sleep(t);
        }
    }
};
