#include <fstream>
#include <iostream>

int main() {
    std::ifstream in;
    int n = 1;
    in.open("inpu.txt");
    if (in) {
        std::cout << "hi\n";
    } else {
        std::cerr << "# error: could not read\n";
    }
    while (in) {
        in >> n;
    }
    in.close();
    std::cout << n << '\n';

    return 0;
}