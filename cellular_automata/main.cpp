#include "lattice_gas.hpp"

int main(int argc, char** argv) {
    int N = 10;
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-N")) {
            N = atoi(argv[++i]);
        }
    }

	LatticeGas gas(N);
	gas.run();

	return 0;
}

