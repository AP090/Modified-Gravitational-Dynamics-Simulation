#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <cmath>
#include <eigen3/Eigen/SparseLU>
#include <eigen3/Eigen/Sparse>

double get_source(std::ifstream &densities) {
    const double h = .001;
    double radius = 0;
    double source = 0;
    densities >> radius;
    densities >> source;
    return 2 * h * h * radius * source;
}

int main() {
    time_t start = time(nullptr);

    const int rank = 267999;
    const double h = .001;
    double radius = h;

    std::ifstream sources;
    sources.open("Modified Source Distribution.txt");

    Eigen::SparseMatrix<double> A(rank, rank);
    Eigen::VectorXd b(rank);
    A.reserve(3 * rank - 2);
    A.insert(0, 0) = -4.0/3.0 * (radius + h);
    A.insert(0, 1) = 4.0/3.0 * (radius + h);
    b(0) = get_source(sources);

    for (int i = 1; i < rank - 1; i++) {
        radius += h;
        A.insert(i, i - 1) = 2 * radius - h;
        A.insert(i, i) = -4 * radius;
        A.insert(i, i + 1) = 2 * radius + h;
        b(i) = get_source(sources);
    }
    A.insert(rank - 1, rank - 2) = 2 * (radius + h) - h;
    A.insert(rank - 1, rank - 1) = -4 * (radius + h);
    b(rank - 1) = get_source(sources);

    A.makeCompressed();

    Eigen::VectorXd x(rank);
    Eigen::SparseLU<Eigen::SparseMatrix<double>, Eigen::COLAMDOrdering<int>> solver;
    solver.analyzePattern(A);
    solver.factorize(A);
    x = solver.solve(b);

    std::ofstream potential;
    potential.open("MOND Galactic Potential.txt");
    radius = h;

    for (int i = 0; i < rank; i++) {
        potential << radius << "\t" << x(i) << std::endl;
        radius += h;
    }

    sources.close();
    potential.close();
    std::cout << "Execution Time: " << time(nullptr) - start << " s." << std::endl;
    return 0;
}
