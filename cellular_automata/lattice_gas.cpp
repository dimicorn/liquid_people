#include "lattice_gas.hpp"

LatticeGas::LatticeGas() {
    initNodes();
} 

void LatticeGas::run() {
    
	sf::Time t = sf::milliseconds(500);
    while(window.isOpen()) {
        window.clear();

        drawGrid();
        drawNodes();
        window.display();
        handleEvents();
        sf::sleep(t);
	}	
}

std::pair<UnitVector, bool> LatticeGas::randomVelocity(const int &i, const int &j) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist8(1, 8);
    int rnd = dist8(rng);
    if (rnd % 8 == 0) {
        return std::make_pair(zero, true);
    } else if (rnd % 8 == 1) {
        return std::make_pair(left, false);
    } else if (rnd % 8 == 2) {
        return std::make_pair(right, false);
    } else if (rnd % 8 == 3) {
        return std::make_pair(top_left, false);
    } else if (rnd % 8 == 4) {
        return std::make_pair(top_right, false);
    } else if (rnd % 8 == 5) {
        return std::make_pair(bottom_left, false);
    } else if (rnd % 8 == 6) {
        return std::make_pair(bottom_right, false);
    } else {
        return std::make_pair(zero, false);
    }
    
}

void LatticeGas::initNodes() {
    Node n = {};
    UnitVector vel = {};
    bool isWall, isEmpty;

    for (int j = 0; j <= c_width; ++j) {
        if (j % 2 == 0) {
            for (int i = 0; i <= c_height; ++i) {
                isWall = false;
                std::pair<UnitVector, bool> res = randomVelocity(i, j);
                vel = res.first, isEmpty = res.second;
                if (i == 0 || i == c_height || j == 0 || j == c_width) {
                    isWall = true;
                }
                n = {vel, dl + i * cell_size, dl + j * sqrt3_2 * cell_size,
                    isEmpty, isWall};
                nodes.push_back(n);
            }
        } else {
            for (int i = 0; i <= c_height + 1; ++i) {
                isWall = false;
                std::pair<UnitVector, bool> res = randomVelocity(i, j);
                vel = res.first, isEmpty = res.second;
                if (i == 0 || i == c_height + 1 || j == c_width) {
                    isWall = true;
                }
                n = {vel, dl + (i - 0.5) * cell_size, dl + j * sqrt3_2 * cell_size,
                    isEmpty, isWall};
                nodes.push_back(n);
            }
        }
    }
}

void LatticeGas::drawNodes() {
    for (const auto &n : nodes) {
        drawNode(n);
    }
}

int LatticeGas::index(const int &i, const int &j) {
    return j * c_width + i;
}

void LatticeGas::drawNode(const Node &n) {
   if (n.isEmpty) {
       return;
   }
   UnitVector vel = n.velocity;

   if (vel == zero) {
       double radius = cell_size / 16;
       sf::CircleShape node(radius);
       node.setPosition(n.x - radius, n.y - radius);
       node.setFillColor(sf::Color::Green);
       window.draw(node);        
       return;
   }

   sf::Vector2f start = sf::Vector2f(n.x, n.y);
   sf::Vector2f end;

   
   if (vel == left) {
        end = sf::Vector2f(n.x + 0.5 * left.x * cell_size, n.y + 0.5 * left.y * cell_size);
   } else if (vel == right) {
        end = sf::Vector2f(n.x + 0.5 * right.x * cell_size, n.y + 0.5 * right.y * cell_size);
   } else if (vel == top_left) {
        end = sf::Vector2f(n.x + 0.5 * top_left.x * cell_size, n.y + 0.5 * top_left.y * cell_size);
   } else if (vel == top_right) {
        end = sf::Vector2f(n.x + 0.5 * top_right.x * cell_size, n.y + 0.5 * top_right.y * cell_size);
   } else if (vel == bottom_left) {
        end = sf::Vector2f(n.x + 0.5 * bottom_left.x * cell_size,
                n.y + 0.5 * bottom_left.y * cell_size);
   } else if (vel == bottom_right) {
        end = sf::Vector2f(n.x + 0.5 * bottom_right.x * cell_size,
                n.y + 0.5 * bottom_right.y * cell_size);
   }

    sf::Vertex node[] = {
        sf::Vertex(start, sf::Color::Green),
        sf::Vertex(end, sf::Color::Green)
    };
    window.draw(node, 2, sf::Lines);
}

void LatticeGas::drawGrid() {
    for (int j = 0; j < c_width / 2; ++j) {
        for (int i = 0; i < 2 * c_height + 1; ++i) {
            drawTriangle(i, j);
            drawRTriangle(i, j);
        }
    }
}

void LatticeGas::drawTriangle(const int &i, const int &j) {
    sf::Vertex left[] = {
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i - 1) * cell_size,
        dl + (0.5 * (i%2 + 1) + j) * sqrt3 * cell_size),
        sf::Color::Red),
        sf::Vertex(sf::Vector2f(dl + 0.5 * i * cell_size,
        dl + (0.5 * (i%2) + j) * sqrt3 * cell_size), sf::Color::Red)
    };
    sf::Vertex right[] = {
        sf::Vertex(sf::Vector2f(dl + 0.5 * i * cell_size,
        dl + (0.5 * (i%2) + j) * sqrt3 * cell_size), sf::Color::Red),
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i + 1) * cell_size,
        dl + (0.5 * (i%2 + 1) + j) * sqrt3 * cell_size), sf::Color::Red)
    };
    sf::Vertex bottom[] = {
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i + 1) * cell_size,
        dl + (0.5 * (i%2 + 1) + j) * sqrt3 * cell_size), sf::Color::Red),
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i - 1) * cell_size,
        dl + (0.5 * (i%2 + 1) + j) * sqrt3 * cell_size),
        sf::Color::Red),
    };

    window.draw(left, 2, sf::Lines);
    window.draw(right, 2, sf::Lines);
    window.draw(bottom, 2, sf::Lines);
}

void LatticeGas::drawRTriangle(const int &i, const int &j) {
    sf::Vertex left[] = {
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i - 1) * cell_size,
        dl + (0.5 * (-i%2 + 1) + j) * sqrt3 * cell_size), sf::Color::Red),
        sf::Vertex(sf::Vector2f(dl + 0.5 * i * cell_size,
        dl + (0.5 * (-i%2) + j + 1) * sqrt3 * cell_size), sf::Color::Red)
    };
    sf::Vertex right[] = {
        sf::Vertex(sf::Vector2f(dl + 0.5 * i * cell_size,
        dl + (0.5 * (-i%2) + j + 1) * sqrt3 * cell_size), sf::Color::Red),
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i + 1) * cell_size,
        dl + (0.5 * (-i%2 + 1) + j) * sqrt3 * cell_size), sf::Color::Red)
    };
    sf::Vertex top[] = {
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i + 1) * cell_size,
        dl + (0.5 * (-i%2 + 1) + j) * sqrt3 * cell_size), sf::Color::Red),
        sf::Vertex(sf::Vector2f(dl + 0.5 * (i - 1) * cell_size,
        dl + (0.5 * (-i%2 + 1) + j) * sqrt3 * cell_size), sf::Color::Red),
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

