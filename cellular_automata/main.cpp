#include "game_of_life.hpp"
#include "lattice_gas.hpp"

int main(int argc, char** argv) {
    /*
	GameOfLife game;
	game.run();
    */
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

