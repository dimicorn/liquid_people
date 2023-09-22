#include "mol_dynamics.hpp"

int main(int argc, char* argv[]) {
	int N = 3;
	for (int i = 1; i < argc; ++i) {
		if (!strcmp(argv[i], "-N")) {
			N = atoi(argv[++i]);
		}
	}

	Simulation sim = Simulation(N);
	sim.run();

	return 0;
}
