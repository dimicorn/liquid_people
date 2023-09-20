#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <cmath>

auto& ran_exp = gsl_ran_exponential;

class Molecule {
public:
	double m, vx, vy;
	double x, y, fx, fy;
	double radius = 10 * m;
	Molecule(double x, double y, double vx, double vy, double fx = 0, double fy = 0, double m = 1): 
		x(x), y(y), vx(vx), vy(vy), fx(fx), fy(fy), m(m) {};

	bool operator ==(const Molecule &m) const {
		if (x == m.x && y == m.y && vx == m.vx && vy == m.vy && fx == m.fx && fy == m.fy) {
			return true;
		}
		return false;
	}

	double kin_energy() {
		double v2 = vx * vx + vy * vy;
		return m * v2 / 2;
	}

	void move1(const double dt) {
		x += vx * dt + 0.5 * dt * dt * fx;
		y += vy * dt + 0.5 * dt * dt * fy;
		vx += 0.5 * dt * fx;
		vy += 0.5 * dt * fy;
	}

	void move2(const double dt) {
		vx += 0.5 * dt * fx;
		vy += 0.5 * dt * fy;
	}

	void check(const double dl, const double w, const double h) {
		if (!(dl - radius <= x - radius && x + radius <= w + dl - radius)) {
			vx = -vx;
		}
		if (!(dl - radius <= y - radius && y + radius <= h + dl - radius)) {
			vy = -vy;
		}
	}

	void print() {
		printf("m = %lf, x = %lf, y = %lf, vx = %lf, vy = %lf\n", m, x, y, vx, vy);
	}
};

double lennard(const double r2) {
	double r6i = 1. / (r2 * r2 * r2);
	return 4 * (r6i * r6i - r6i);
}

void collisions(std::vector<Molecule> &mols) {
	// double rc2 = 25;

	for (auto &i : mols) {
		for (auto &j : mols) {
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
			if (std::sqrt(r2) <= 5) {
				double r6i = 1. / (r2 * r2 * r2);
				double f = 48 * (r6i * r6i - 0.5 * r6i);
				mols[i].fx += dx * f / r2;
				mols[j].fx -= dx * f / r2;
				mols[i].fy += dy * f / r2;
				mols[j].fy -= dy * f / r2;
			}
			*/
		}
	}
}


int main() {
	const double window_width = 600;
	const double window_height = 600;
	const double dl = 50;
	const double width = window_width - 2 * dl;
	const double height = window_height - 2 * dl;

	gsl_rng* r = gsl_rng_alloc(gsl_rng_mt19937);
  	unsigned long int Seed = 23410981;
	gsl_rng_set(r, Seed);
	
	int N = 5;
	std::vector<Molecule> molecules;
	for (int i = 0; i < N; ++i) {
		double x = 100 - 10 * i;
		double y = 100 - 10 * i;
		double vx = ran_exp(r, 0.1);
		double vy = ran_exp(r, 0.1);
		Molecule m = Molecule(x, y, vx, vy);
		molecules.push_back(m);	
	}

	std::string windowTitle = "MD Simulation";

	sf::Time t = sf::milliseconds(1);
	const double dt = 1;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), windowTitle);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
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
		for (auto &m : molecules) {
			m.move1(dt);
			m.check(dl, width, height);
		}

		collisions(molecules);

		for (auto &m : molecules) {
			m.move2(dt);
    		sf::CircleShape point(m.radius);
			point.setPosition(m.x, m.y);
    		point.setFillColor(sf::Color::Green);
        	window.draw(point);
		}
        window.display();
		sf::sleep(t);

    }
    return 0;
}
