#pragma once

#include <vector>

using namespace std;

struct Acceleration
{
    double ax;
    double ay;

    vector<vector<double>> getMatrix() const
    {
        return {
            {ax},
            {ay}
        };
    }
};

struct State
{
    double x;
    double y;
    double vx;
    double vy;

    vector<vector<double>> getMatrix() const
    {
        return {
            {x},
            {y},
            {vx},
            {vy}
        };
    }
};

State propagate(
    const State& state,
    const Acceleration& accel,
    double dt
);

State propagateMatrix(
    const State& state,
    const Acceleration& accel,
    double dt
);

vector<vector<double>> multiplyMatrices(
    const vector<vector<double>>& A,
    const vector<vector<double>>& B
);

vector<vector<double>> addMatrices(
    const vector<vector<double>>& A,
    const vector<vector<double>>& B,
    int rows1,
    int cols1,
    int rows2,
    int cols2
);