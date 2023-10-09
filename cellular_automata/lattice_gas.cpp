#include "lattice_gas.hpp"

LatticeGas::LatticeGas(): cell_size(100), dl(50), w_width(600), w_height(600),
width(w_width - 2 * dl), height(w_height - 2 * dl), c_width(width / cell_size),
c_height(height / (cell_size * sqrt3_2)), window({w_width, w_height}, "Lattice Gas Cellular Automata") {
    initNodes();
} 

void LatticeGas::run() {
	sf::Time t = sf::milliseconds(500);
    while(window.isOpen()) {
        window.clear();

		drawBox();
		

        window.display();
        handleEvents();
        sf::sleep(t);
	}	
}

void LatticeGas::initNodes() {
	bool isEmpty = false;
	for (int i = 0; i < c_height; ++i) {
		for (int j = 0; j < c_width; ++j) {
			bool isWall = (i == 0 || i + 1 >= c_height) ? true : false;
			Node n = {right, i * cell_size, j * sqrt3_2, isEmpty, isWall};
			nodes.push_back(n);
		}
	}
}

void LatticeGas::drawNodes() {
	for (auto &n : nodes) {
		if (!(n.isEmpty && n.isWall)) {
    		sf::Vertex right[] = {
        	sf::Vertex(sf::Vector2f(dl + , dl), sf::Color::Green),
        	sf::Vertex(sf::Vector2f(dl + cell_size / 2, dl + cell_size * sqrt(3)/2), sf::Color::Green)
			};



void LatticeGas::drawTriangle() {
    sf::Vertex left[] = {
        sf::Vertex(sf::Vector2f(dl, dl), sf::Color::Green),
        sf::Vertex(sf::Vector2f(dl - cell_size / 2, dl + cell_size * sqrt(3)/2), sf::Color::Green)
    };
    sf::Vertex right[] = {
        sf::Vertex(sf::Vector2f(dl, dl), sf::Color::Green),
        sf::Vertex(sf::Vector2f(dl + cell_size / 2, dl + cell_size * sqrt(3)/2), sf::Color::Green)
    };
    sf::Vertex bottom[] = {
        sf::Vertex(sf::Vector2f(dl - cell_size / 2, dl + cell_size * sqrt(3)/2), sf::Color::Green),
        sf::Vertex(sf::Vector2f(dl + cell_size / 2, dl + cell_size * sqrt(3)/2), sf::Color::Green)
    };

    window.draw(left, 2, sf::Lines);
    window.draw(right, 2, sf::Lines);
    window.draw(bottom, 2, sf::Lines);
}

void LatticeGas::drawRTriangle() {
    sf::Vertex top[] = {
        sf::Vertex(sf::Vector2f(dl, dl), sf::Color::Green),
        sf::Vertex(sf::Vector2f(dl + cell_size, dl), sf::Color::Green)
    };
    sf::Vertex left[] = {
        sf::Vertex(sf::Vector2f(dl, dl), sf::Color::Green),
        sf::Vertex(sf::Vector2f(dl + cell_size / 2, dl + cell_size * sqrt(3)/2), sf::Color::Green)
    };
    sf::Vertex right[] = {
        sf::Vertex(sf::Vector2f(dl + cell_size, dl), sf::Color::Green),
        sf::Vertex(sf::Vector2f(dl + cell_size / 2, dl + cell_size * sqrt(3)/2), sf::Color::Green)
    };

    window.draw(top, 2, sf::Lines);
    window.draw(left, 2, sf::Lines);
    window.draw(right, 2, sf::Lines);
}
void LatticeGas::drawBox() {
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

    window.draw(bottom, 2, sf::Lines);
    window.draw(top, 2, sf::Lines);
    window.draw(left, 2, sf::Lines);
    window.draw(right, 2, sf::Lines);
}

void LatticeGas::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}
