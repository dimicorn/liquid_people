#pragma once
#include <cmath>
#include <iostream>

const double sqrt3_2 = sqrt(3) / 2;
const double sqrt3 = sqrt(3);

class UnitVector {
public:
    double x, y;

    UnitVector(const double &x = 0, const double &y = 0): x(x), y(y) {};

    bool operator==(const UnitVector &v) const {
        return (x == v.x && y == v.y);
    }   
};

class Hash {
public:
    size_t operator() (const UnitVector &v) const {
        return (std::hash<double>()(v.x)) ^ (std::hash<double>()(v.y));
    }
};

const UnitVector zero(0, 0);
const UnitVector left(-1, 0);
const UnitVector right(1, 0);
const UnitVector top_left(-0.5, -sqrt3_2);
const UnitVector top_right(0.5, -sqrt3_2);
const UnitVector bottom_left(-0.5, sqrt3_2);
const UnitVector bottom_right(0.5, sqrt3_2);
