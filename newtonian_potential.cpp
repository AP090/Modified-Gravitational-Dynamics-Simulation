#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <cmath>
#include <eigen3/Eigen/SparseLU>
#include <eigen3/Eigen/Sparse>

double get_source(std::ifstream &densities) {
    const double h = .001;
    const double G = 4.51710E-39;
    double radius = 0;
    double density = 0;
    densities >> radius;
    densities >> density;
    return 2 * h * h * radius * 4 * M_PI * G * density;
}

int main() {
    time_t start = time(nullptr);
    std::cout << "Started" << std::endl;
    
    const int rank = 267999;
    const double h = .001;
    double radius = h;

    std::ifstream densities;
    densities.open("Modified Mass Distribution.txt");

    Eigen::SparseMatrix<double> A(rank, rank);
    Eigen::VectorXd b(rank);
    A.reserve(3 * rank - 2);
    A.insert(0, 0) = -4.0/3.0 * (radius + h);
    A.insert(0, 1) = 4.0/3.0 * (radius + h);
    b(0) = get_source(densities);

    for (int i = 1; i < rank - 1; i++) {
        radius += h;
        A.insert(i, i - 1) = 2 * radius - h;
        A.insert(i, i) = -4 * radius;
        A.insert(i, i + 1) = 2 * radius + h;
        b(i) = get_source(densities);
    }
    A.insert(rank - 1, rank - 2) = 2 * (radius + h) - h;
    A.insert(rank - 1, rank - 1) = -4 * (radius + h);
    b(rank - 1) = get_source(densities);

    A.makeCompressed();

    Eigen::VectorXd x(rank);
    Eigen::SparseLU<Eigen::SparseMatrix<double>, Eigen::COLAMDOrdering<int>> solver;
    solver.analyzePattern(A);
    solver.factorize(A);
    x = solver.solve(b);

    std::ofstream potential;
    potential.open("Newtonian Galactic Potential.txt");
    radius = h;

    for (int i = 0; i < rank; i++) {
        potential << radius << "\t" << x(i) << std::endl;
        radius += h;
    }

    densities.close();
    potential.close();
    std::cout << "Execution Time: " << time(nullptr) - start << " s." << std::endl;
    return 0;
}
