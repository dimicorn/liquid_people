#ifndef MOL_DYNAMICS_HPP
#define MOL_DYNAMICS_HPP

#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class Molecule {
private:
	double kin_energy();

public:
	double m, x, y;
	double vx, vy, fx, fy;
	const unsigned int radius;

	Molecule(double x, double y, double vx, double vy, double fx, double fy, double m);
	bool operator ==(const Molecule &m) const;
	void print();
};

class Simulation {
private:
	const unsigned int w_width, w_height;
    const double dl, width, height, dt;
    sf::RenderWindow window;
    std::vector<Molecule> molecules;
	const int N;

	double lennard(const double r2);

	void initMols();
	void moveMols();
	void collision_check(Molecule &i);
	void drawBox();
	void handleEvents();

public:
	Simulation(const int N);
    void run();
};
#endif
