#include "mol_dynamics.hpp"
#include <cmath>

Molecule::Molecule(const double &x, const double &y, const double &vx, const double &vy,
const double &fx, const double &fy, const double &m): 
m(m), x(x), y(y), vx(vx), vy(vy), fx(fx), fy(fy) {};

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

Simulation::Simulation(const int &N): N(N) {
	initMols();
}

double Simulation::lennard(const double &r2) {
    double r6i = 1. / (r2 * r2 * r2);
    return 4 * (r6i * r6i - r6i);
}

void Simulation::initMols() {
	std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distv(1, 3);
    std::uniform_int_distribution<std::mt19937::result_type> distx(100, 400);
    
    int count = 0;
    for (int i = 50; i < 500; i += 50) {
        for (int j = 50; j < 500; j += 50) {
            if (count < N) {
                double vx = distv(rng) / 1000.;
                double vy = distv(rng) / 1000.;
                Molecule m = Molecule(i + dl, j + dl, vx, vy);
                molecules.push_back(m);
                ++count;
            }
        }
    }

    /*
    for (int i = 0; i < N; ++i) {
        double x = distx(rng);
        double y = distx(rng);
        double vx = distv(rng) / 1000.;
        double vy = distv(rng) / 1000.;
        Molecule m = Molecule(x, y, vx, vy);
        molecules.push_back(m);
    }
    */
}

void Simulation::run() {
	while (window.isOpen()) {
		handleEvents();
		window.clear();

		moveMols();
		// drawBox();
        drawPipe();
        data();

		window.display();
	}
    std::cout << "N :" << molecules.size() << '\n';
}

void Simulation::data() {
    double T, mean_v, sum_vel2_2 = 0;
    double sum_vel_2 = 0;
    double v, v2, sigma = 0;
    for (const auto &m : molecules) {
        v2 = m.vx * m.vx + m.vy * m.vy;
        v = sqrt(v2);
        sum_vel2_2 += v2 / 2;
        sum_vel_2 += v;
        sigma += m.vx * m.vy;
    }
    T = sum_vel2_2 / molecules.size();
    mean_v = sum_vel_2 / molecules.size();
    std::cout << "Temperature: " << T << ' ';
    std::cout << "Sigma: " << sigma << ' ';
    std::cout << "Mean velocity: " << mean_v << '\n';

}

double Simulation::gx(const double &x, const double &y) {
    return -k * x / ((1500 - x) * (1500 - x) + ((height + dl)/2 - y) * ((height + dl)/2 - y));
}

double Simulation::gy(const double &x, const double &y) {
    return -k * y / ((1500 - x) * (1500 - x) + ((height + dl)/2 - y) * ((height + dl)/2 - y));
}


void Simulation::moveMols() {
	for (auto &m : molecules) {
		// changing coordinates and velocities
		m.x += m.vx * dt + 0.5 * dt * dt * (m.fx + gx(m.x, m.y));
        m.y += m.vy * dt + 0.5 * dt * dt * (m.fy + gy(m.x, m.y));

        m.vx += 0.5 * dt * (m.fx + gx(m.x, m.y));
        m.vy += 0.5 * dt * (m.fy + gy(m.x, m.y));

		// checking if molecule is out of the box
        /*
		if (!(dl + m.radius <= m.x && m.x <= width + dl - m.radius)) {
            m.vx = -m.vx;
        }
        if (!(dl + m.radius<= m.y && m.y <= height + dl - m.radius)) {
            m.vy = -m.vy;
        }
        */
        if ((dl + m.radius > m.y || m.y > dl + height - m.radius) && 
                dl + m.radius <= m.x && m.x <= dl + width - m.radius) {
            m.vy = -m.vy;
        }

        if (dl + m.radius > m.x && dl + m.radius <= m.y && m.y <= dl + height - m.radius) {
            m.vx = -m.vx;
        }

        // top right
        if (m.x > dl + width - m.radius && dl + m.radius <= m.y &&
                m.y <= (height + dl) / 2 - half_pipe + m.radius) {
            m.vx = -m.vx;
        }
        
        // bottom right
        if (m.x > dl + width - m.radius && (height + dl) / 2 + half_pipe <= m.y &&
                m.y <= dl + height - m.radius) {
            m.vx = -m.vx;
        }

        if (width + dl <= m.x && m.x <= width + dl + half_pipe && 
        ((height + dl)/2 - half_pipe + m.radius > m.y || (height + dl) / 2 + half_pipe - m.radius < m.y)) {
            m.vy = -m.vy;
        }
		// collisions
		collision_check(m);

		// changing velocities;
		m.vx += 0.5 * dt * (m.fx + gx(m.x, m.y));
    	m.vy += 0.5 * dt * (m.fy + gy(m.x, m.y));
		
		// drawing molecule
		sf::CircleShape ball(m.radius);
    	ball.setPosition(m.x-m.radius, m.y-m.radius);
    	ball.setFillColor(sf::Color::Green);
    	window.draw(ball);
	}
}

void Simulation::collision_check(Molecule &i) {
	double rc2 = 50;
    for (auto &j : molecules) {
        if (i == j) {
            continue;
        }
        double dx = i.x - j.x;
        double dy = i.y - j.y;
        double r2 = dx * dx + dy * dy;

        // elastic collision
        if (std::sqrt(r2) <= i.radius + j.radius) {
            double coef = ((i.vx - j.vx) * dx + (i.vy - j.vy) * dy) / r2;
            i.vx -= coef * dx;
            i.vy -= coef * dy;
            j.vx += coef * dx;
            j.vy += coef * dy;
        }
        // Lennard-Jones potential
        if (r2 <= rc2) {
            double r6i = pow(10, 6)/ (r2 * r2 * r2);
            double f = 48 * (r6i * r6i - r6i);
            i.fx += dx * f / r2;
            j.fx -= dx * f / r2;
            i.fy += dy * f / r2;
            j.fy -= dy * f / r2;
        }
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

void Simulation::drawPipe() {
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
    sf::Vertex top_right[] = {
        sf::Vertex(sf::Vector2f(width + dl, dl), sf::Color::Red),
        sf::Vertex(sf::Vector2f(width + dl, (height + dl)/2 - half_pipe), sf::Color::Red)
    };
    sf::Vertex bottom_right[] = {
        sf::Vertex(sf::Vector2f(width + dl, (height + dl)/2 + half_pipe), sf::Color::Red),
        sf::Vertex(sf::Vector2f(width + dl, height + dl), sf::Color::Red)
    };
    sf::Vertex top_pipe[] = {
        sf::Vertex(sf::Vector2f(width + dl, (height + dl)/2 - half_pipe), sf::Color::Red),
        sf::Vertex(sf::Vector2f(width + dl + half_pipe, (height + dl)/2 - half_pipe), sf::Color::Red)
    };
    sf::Vertex bottom_pipe[] = {
        sf::Vertex(sf::Vector2f(width + dl, (height + dl)/2 + half_pipe), sf::Color::Red),
        sf::Vertex(sf::Vector2f(width + dl + half_pipe, (height + dl)/2 + half_pipe), sf::Color::Red)
    };
    window.draw(bottom, 2, sf::Lines);
    window.draw(top, 2, sf::Lines);
    window.draw(left, 2, sf::Lines);
    window.draw(top_right, 2, sf::Lines);
    window.draw(bottom_right, 2, sf::Lines);
    window.draw(top_pipe, 2, sf::Lines);
    window.draw(bottom_pipe, 2, sf::Lines);

}

void Simulation::handleEvents() {
	sf::Event event;
	while(window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
	}
}

