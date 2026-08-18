#include "state.h"
#include <vector>
#include <stdexcept>
using namespace std;

// simple propagate function
State propagate(const State& state, const Acceleration& accel, double dt)
{
    State newState;

    newState.x = state.x + state.vx * dt + 0.5 * accel.ax * dt * dt;
    newState.y = state.y + state.vy * dt+ 0.5 * accel.ay * dt * dt;
    newState.vx = state.vx + accel.ax * dt;
    newState.vy = state.vy + accel.ay * dt;

    return newState;
}

// matrix multiplication function
vector<vector<double>> multiplyMatrices(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int colsB = B[0].size();

    vector<vector<double>> result(rowsA, vector<double>(colsB, 0.0));

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}

vector<vector<double>> addMatrices(const vector<vector<double>>& A, const vector<vector<double>>& B, int rows1, int cols1, int rows2, int cols2) {
    if (rows1 != rows2 || cols1 != cols2) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition.");
    }
    vector<vector<double>> result(rows1, vector<double>(cols1, 0.0));
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

// propagate function using matrix multiplication (remember linear algebra?)
State propagateMatrix(const State& state, const Acceleration& accel, double dt)
{
    State newState;
    // Fx(t) term
    vector<vector<double>> F = {
        {1, 0, dt, 0},
        {0, 1, 0, dt},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    
    // Bu(t) term
    vector<vector<double>> B = {
        {0.5 * dt * dt, 0},
        {0, 0.5 * dt * dt},
        {dt, 0},
        {0, dt}
    };

    auto stateMatrix = state.getMatrix();
    auto accelMatrix = accel.getMatrix();
    vector<vector<double>> matrix1 = multiplyMatrices(F, stateMatrix);
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    vector<vector<double>> matrix2 = multiplyMatrices(B, accelMatrix);
    int rows2 = matrix2.size();
    int cols2 = matrix2[0].size();


    vector<vector<double>> newStateMatrix = addMatrices(matrix1, matrix2, rows1, cols1, rows2, cols2);

    newState.x = newStateMatrix[0][0];
    newState.y = newStateMatrix[1][0];
    newState.vx = newStateMatrix[2][0];
    newState.vy = newStateMatrix[3][0];

    return newState;
}