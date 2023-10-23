#pragma once
#include "unit_vector.hpp"
#include <unordered_set>

class Node {
public:
    std::unordered_set<UnitVector, Hash> velocities;
    double x, y;
    unsigned long int particleCount; // same as velocities.size()
    bool isWall; // for testing purposes
                 
    Node(const std::unordered_set<UnitVector, Hash> &vels = {}, const double &x = 0, 
            const double &y = 0, const int &count = 0, const bool &wall = true):
        velocities(vels), x(x), y(y), particleCount(count), isWall(wall) {};
};
