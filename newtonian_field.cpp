#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <cmath>
#include <eigen3/Eigen/SparseLU>
#include <eigen3/Eigen/Sparse>

double source(const double radius, const double density) {
    const double h = .001;
    const double G = 4.51710E-39;
    if (density == 0) {
        return 0;
    }
    return -1 * 8 * h * M_PI * G * radius * density;
}

double read_density(std::ifstream &densities) {
    double radius = 0;
    double density = 0;
    densities >> radius;
    densities >> density;
    return density;
}

int main() {
    time_t start = time(nullptr);

    const int rank = 267999;
    const double h = .001;
    double radius = h;

    std::ifstream densities;
    densities.open("Modified Mass Distribution.txt");

    Eigen::SparseMatrix<double> A(rank, rank);
    Eigen::VectorXd b(rank);
    A.reserve(2 * rank - 1);
    A.insert(0, 0) = -4.0/3.0;
    A.insert(0, 1) = 4.0/3.0;
    b(0) = source(radius, read_density(densities));

    for (int i = 1; i < rank - 1; i++) {
        A.insert(i, i - 1) = -1;
        A.insert(i, i + 1) = 1;
        radius += h;
        b(i) = source(radius, read_density(densities));
    }
    A.insert(rank - 1, rank - 2) = -1;
    b(rank - 1) = source(radius + h, read_density(densities));
    A.makeCompressed();

    Eigen::VectorXd x(rank);
    Eigen::SparseLU<Eigen::SparseMatrix<double>, Eigen::COLAMDOrdering<int>> solver;
    solver.analyzePattern(A);
    solver.factorize(A);
    x = solver.solve(b);

    std::ofstream field;
    field.open("Newtonian Galactic Field.txt");
    radius = h;

    for (int i = 0; i < rank; i++) {
        double g = x(i) / radius;
        field << radius << "\t" << g << std::endl;
        radius += h;
    }

    densities.close();
    field.close();
    std::cout << "Execution Time: " << time(nullptr) - start << " s." << std::endl;
    return 0;
}
