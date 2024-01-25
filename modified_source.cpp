#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <cmath>
#include <complex>
#include "quartic.h"

double find_g(const double g_N) {
    const double a0 = 3.889E-28;
    std::complex<double>* solutions = solve_quartic(0, -(g_N * g_N), 0, -(g_N * g_N)*(a0 * a0));
    double sol = 0;
    for (int i = 0; i < 4; i++) {
        if (solutions[i].imag() == 0.0) {
            sol = solutions[i].real();
            break;
        }
    }
    delete[] solutions;
    return std::abs(sol);
}

int main() {
    time_t start = time(nullptr);

    const double a0 = 3.889E-28;
    const double h = .001;

    std::ifstream field;
    field.open("Newtonian Galactic Field.txt");

    std::ofstream source;
    source.open("Modified Source Distribution.txt");

    double radii[3]{};
    double g_fields[3]{};

    field >> radii[1];
    field >> g_fields[1];
    field >> radii[2];
    field >> g_fields[2];
    double correction = sqrt(1 + pow(a0 / find_g(g_fields[1]), 2));

    double new_source = -(correction / radii[1]) * ((radii[2] * g_fields[2]) / (2 * h));
    source << radii[1] << "\t" << new_source << std::endl;

    radii[0] = radii[1];
    g_fields[0] = g_fields[1];
    radii[1] = radii[2];
    g_fields[1] = g_fields[2];
    double temp = 0;

    while (field >> radii[2]) {
        temp = radii[2];
        field >> g_fields[2];

        double correction = sqrt(1 + pow(a0 / find_g(g_fields[1]), 2));
        double new_source = -(correction / radii[1]) * ((radii[2] * g_fields[2] - radii[0] * g_fields[0]) / (2 * h));
        source << radii[1] << "\t" << new_source << std::endl;

        radii[0] = radii[1];
        g_fields[0] = g_fields[1];
        radii[1] = radii[2];
        g_fields[1] = g_fields[2];
    }

    correction = sqrt(1 + pow(a0 / find_g(g_fields[2]), 2));
    new_source = -(correction / temp) * ((-radii[0] * g_fields[0]) / (2 * h));
    source << temp << "\t" << new_source << std::endl;

    field.close();
    source.close();
    std::cout << "Execution Time: " << time(nullptr) - start << " s." << std::endl;
    return 0;
}
