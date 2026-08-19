#include <cassert>
#include <cmath>
#include <iostream>

#include "state.h"

bool nearlyEqual(double a, double b, double epsilon = 1e-9)
{
    return std::abs(a - b) < epsilon;
}

void testPropagate()
{
    State state{10.0, 20.0, 5.0, -2.0};
    Acceleration accel{2.0, -3.0};
    double dt = 0.5;

    State direct = propagate(state, accel, dt);
    State matrix = propagateMatrix(state, accel, dt);

    assert(nearlyEqual(direct.x, matrix.x));
    assert(nearlyEqual(direct.y, matrix.y));
    assert(nearlyEqual(direct.vx, matrix.vx));
    assert(nearlyEqual(direct.vy, matrix.vy));
    assert(nearlyEqual(direct.x, 12.75));
    assert(nearlyEqual(direct.y, 18.625));
    assert(nearlyEqual(direct.vx, 6.0));
    assert(nearlyEqual(direct.vy, -3.5));

    std::cout << "testPropagate: PASSED\n";
}

int main()
{
    testPropagate();

    std::cout << "All tests passed!\n";
}