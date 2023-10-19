#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class Molecule {
private:
	double kin_energy();

public:
	double m, x, y;
	double vx, vy, fx, fy;
	const unsigned int radius = 10;

	Molecule(const double &x, const double &y, const double &vx, const double &vy, 
    const double &fx = 0, const double &fy = 0, const double &m = 1);
	bool operator ==(const Molecule &m) const;
	void print();
};

class Simulation {
private:
	const unsigned int w_width = 600, w_height = 600;
    const double dl = 50, dt = 1;
    const double width = w_width - 2 * dl;
    const double height = w_height - 2  * dl;
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(w_width, w_height), "MD Simulation");
    std::vector<Molecule> molecules;
	const int N;

	double lennard(const double &r2);

	void initMols();
	void moveMols();
	void collision_check(Molecule &i);
	void drawBox();
	void handleEvents();

public:
	Simulation(const int &N);
    void run();
};
