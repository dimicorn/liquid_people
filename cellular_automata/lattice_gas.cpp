#include "lattice_gas.hpp"

LatticeGas::LatticeGas() {
    initNodes();
} 

void LatticeGas::run() {
	sf::Time t = sf::milliseconds(500);
    while(window.isOpen()) {
        window.clear();

		drawBox();

        for (int j = 0; j < c_width / 2; ++j) {
            for (int i = 0; i < 2 * c_height + 1; ++i) {
                drawTriangle(i, j);
                drawRTriangle(i, j);
            }
        }

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

/*
void LatticeGas::drawNodes() {
	for (auto &n : nodes) {
		if (!(n.isEmpty && n.isWall)) {
    		sf::Vertex right[] = {
        	sf::Vertex(sf::Vector2f(dl + , dl), sf::Color::Green),
        	sf::Vertex(sf::Vector2f(dl + cell_size / 2, dl + cell_size * sqrt(3)/2),
            sf::Color::Green)
			};
        }
    }
}
*/

void LatticeGas::drawTriangle(const int &i, const int &j) {
    sf::Vertex left[] = {
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i - 1) * cell_size,
        dl + (0.5 * (i%2 + 1) + j) * sqrt3 * cell_size),
        sf::Color::Green),
        sf::Vertex(sf::Vector2f(dl + 0.5 * i * cell_size,
        dl + (0.5 * (i%2) + j) * sqrt3 * cell_size), sf::Color::Green)
    };
    sf::Vertex right[] = {
        sf::Vertex(sf::Vector2f(dl + 0.5 * i * cell_size,
        dl + (0.5 * (i%2) + j) * sqrt3 * cell_size), sf::Color::Green),
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i + 1) * cell_size,
        dl + (0.5 * (i%2 + 1) + j) * sqrt3 * cell_size), sf::Color::Green)
    };
    sf::Vertex bottom[] = {
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i + 1) * cell_size,
        dl + (0.5 * (i%2 + 1) + j) * sqrt3 * cell_size), sf::Color::Green),
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i - 1) * cell_size,
        dl + (0.5 * (i%2 + 1) + j) * sqrt3 * cell_size),
        sf::Color::Green),
    };

    window.draw(left, 2, sf::Lines);
    window.draw(right, 2, sf::Lines);
    window.draw(bottom, 2, sf::Lines);
}

void LatticeGas::drawRTriangle(const int &i, const int &j) {
    sf::Vertex left[] = {
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i - 1) * cell_size,
        dl + (0.5 * (-i%2 + 1) + j) * sqrt3 * cell_size), sf::Color::Green),
        sf::Vertex(sf::Vector2f(dl + 0.5 * i * cell_size,
        dl + (0.5 * (-i%2) + j + 1) * sqrt3 * cell_size), sf::Color::Green)
    };
    sf::Vertex right[] = {
        sf::Vertex(sf::Vector2f(dl + 0.5 * i * cell_size,
        dl + (0.5 * (-i%2) + j + 1) * sqrt3 * cell_size), sf::Color::Green),
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i + 1) * cell_size,
        dl + (0.5 * (-i%2 + 1) + j) * sqrt3 * cell_size), sf::Color::Green)
    };
    sf::Vertex top[] = {
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i + 1) * cell_size,
        dl + (0.5 * (-i%2 + 1) + j) * sqrt3 * cell_size), sf::Color::Green),
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i - 1) * cell_size,
        dl + (0.5 * (-i%2 + 1) + j) * sqrt3 * cell_size), sf::Color::Green),
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

