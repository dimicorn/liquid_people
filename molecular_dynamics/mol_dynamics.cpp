#include "mol_dynamics.hpp"

Molecule::Molecule(double x, double y, double vx, double vy, double fx = 0, double fy = 0, double m = 1):
		x(x), y(y), vx(vx), vy(vy), fx(fx), fy(fy), m(m), radius(10) {};

bool Molecule::operator ==(const Molecule &m) const {
    if (x == m.x && y == m.y && vx == m.vx && vy == m.vy && fx == m.fx && fy == m.fy) {
        return true;
    }
    return false;
}

double Molecule::kin_energy() {
    double v2 = vx * vx + vy * vy;
    return m * v2 / 2;
}

void Molecule::print() {
    printf("m = %lf, x = %lf, y = %lf, vx = %lf, vy = %lf\n", m, x, y, vx, vy);
}

Simulation::Simulation(const int N): w_width(600), w_height(600), dl(50), width(w_width - 2 * dl),
height(w_height - 2 * dl), window({w_width, w_height}, "MD Simulation"), N(N), dt(1) {
	initMols();
}

double Simulation::lennard(const double r2) {
    double r6i = 1. / (r2 * r2 * r2);
    return 4 * (r6i * r6i - r6i);
}

void Simulation::initMols() {
	/*
	std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distv(1, 6);
    std::uniform_int_distribution<std::mt19937::result_type> distx(100, 400);

    for (int i = 0; i < N; ++i) {
        double x = distx(rng);
        double y = distx(rng);
        double vx = distv(rng) / 10;
        double vy = distv(rng) / 10;
        Molecule m = Molecule(x, y, vx, vy);
        molecules.push_back(m);
    }
	*/
	Molecule m = Molecule(100, 100, 0.1, 0.1);
	molecules.push_back(m);
	Molecule m1 = Molecule(150, 150, 0, 0.13);
	molecules.push_back(m1);
}

void Simulation::run() {
	while (window.isOpen()) {
		handleEvents();
		window.clear();

		moveMols();
		// collision_check();
		drawBox();

		window.display();
	}
}

void Simulation::moveMols() {
	for (auto &m : molecules) {
		// changing coordinates and velocities
		m.x += m.vx * dt + 0.5 * dt * dt * m.fx;
        m.y += m.vy * dt + 0.5 * dt * dt * m.fy;
        m.vx += 0.5 * dt * m.fx;
        m.vy += 0.5 * dt * m.fy;

		// checking if molecule is out of the box
		if (!(dl - m.radius <= m.x - m.radius && m.x + m.radius <= width + dl - m.radius)) {
            m.vx = -m.vx;
        }
        if (!(dl - m.radius <= m.y - m.radius && m.y + m.radius <= height + dl - m.radius)) {
            m.vy = -m.vy;
        }

		// collisions
		collision_check(m);

		// changing velocities;
		m.vx += 0.5 * dt * m.fx;
    	m.vy += 0.5 * dt * m.fy;
		
		// drawing molecule
		sf::CircleShape ball(m.radius);
    	ball.setPosition(m.x, m.y);
    	ball.setFillColor(sf::Color::Green);
    	window.draw(ball);
	}
}

void Simulation::collision_check(Molecule &i) {
	// double rc2 = 25;
    for (auto &j : molecules) {
        if (i == j) {
            continue;
        }
        double dx = i.x - j.x;
        double dy = i.y - j.y;
        double r2 = dx * dx + dy * dy;
        // elastic collision
        if (std::sqrt(r2) <= i.radius + j.radius) {
            double coef = (i.vx * j.vx + i.vy * j.vy) / r2;
            i.vx -= coef * dx;
            i.vy -= coef * dy;
            j.vx += coef * dx;
            j.vy += coef * dy;
        }
        // Lennard-Jones potential
        /*
        if (r2 <= rc2) {
            double r6i = 1. / (r2 * r2 * r2);
            double f = 48 * (r6i * r6i - 0.5 * r6i);
            i.fx += dx * f / r2;
            j.fx -= dx * f / r2;
            i.fy += dy * f / r2;
            j.fy -= dy * f / r2;
        }
        */
    }
}

void Simulation::drawBox() {
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

void Simulation::handleEvents() {
	sf::Event event;
	while(window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
	}
}

