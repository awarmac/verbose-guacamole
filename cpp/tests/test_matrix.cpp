#include <cassert>
#include <iostream>
#include <vector>
#include "state.h"

using namespace std;

bool nearlyEqual(double a, double b, double epsilon = 1e-9)
{
    return std::abs(a - b) < epsilon;
}


bool checkMatrix(
    const std::vector<std::vector<double>>& actual,
    const std::vector<std::vector<double>>& expected)
{
    if (actual.size() != expected.size())
    {
        std::cerr << "FAILED: Matrix row dimensions differ\n";
        std::cerr << "  Expected rows: " << expected.size() << '\n';
        std::cerr << "  Actual rows:   " << actual.size() << '\n';

        return false;
    }

    for (size_t i = 0; i < expected.size(); ++i)
    {
        if (actual[i].size() != expected[i].size())
        {
            std::cerr << "FAILED: Matrix column dimensions differ at row "
                      << i << '\n';

            return false;
        }

        for (size_t j = 0; j < expected[i].size(); ++j)
        {
            if (!nearlyEqual(actual[i][j], expected[i][j]))
            {
                std::cerr << "FAILED: Matrix value differs at ["
                          << i << "][" << j << "]\n";

                std::cerr << "  Expected: " << expected[i][j] << '\n';
                std::cerr << "  Actual:   " << actual[i][j] << '\n';

                return false;
            }
        }
    }

    return true;
}

void testMatrixMultiplication()
{
    std::vector<std::vector<double>> A = {
        {1, 2},
        {3, 4}
    };

    std::vector<std::vector<double>> B = {
        {5, 6},
        {7, 8}
    };

    std::vector<std::vector<double>> expected = {
        {19, 22},
        {43, 50}
    };

    auto actual = multiplyMatrices(A, B);

    if (checkMatrix(actual, expected))
    {
        std::cout << "PASS: Matrix multiplication\n";
    }
    else
    {
        std::cerr << "FAIL: Matrix multiplication\n";
    }
}

int main()
{
    testMatrixMultiplication();

    std::cout << "All tests passed!\n";
}