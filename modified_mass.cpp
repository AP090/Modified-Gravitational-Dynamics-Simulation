#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>
#include <thread>

double bulge(const double r, const double z) {
    const double p_0b = 9.73E19;
    const double alpha = 1.8;
    const double r_0 = .075;
    const double r_cut = 2.1;
    const double q = .5;

    const double r_prime = sqrt(r*r + (z/q)*(z/q));
    double density = p_0b * pow(1 + r_prime/r_0, -1 * alpha) * exp(-1 * (r_prime/r_cut)*(r_prime/r_cut));
    if (density < 0) {
        return 0;
    } else {
        return density;
    }
}

double thin_stellar_disc_antiderivative(const double r) {
    const double sigma_0 = 8.96E8;
    const double z_d = .3;
    const double R_d = 2.50;

    double z_f = 1.3;
    double z_i = -1.3;

    double iter1 = 0;
    double iter2 = 0;

    do {
        iter1 = .5 * sigma_0 * exp(-1 * r / R_d) * (-1 * exp(z_i/z_d) - exp(-1 * z_f/z_d) + 2);
        z_f += .001;
        z_i -= .001;
        iter2 = .5 * sigma_0 * exp(-1 * r / R_d) * (-1 * exp(z_i/z_d) - exp(-1 * z_f/z_d) + 2);
    } while (abs(iter2 - iter1) > 1);
    if (iter2 < 0) {
        return 0;
    } else {
        return iter2 / (z_f - z_i);
    }
}

double thick_stellar_disc_antiderivative(const double r) {
    const double sigma_0 = 1.83E8;
    const double z_d = .9;
    const double R_d = 3.02;

    double z_f = 1.3;
    double z_i = -1.3;

    double iter1 = 0;
    double iter2 = 0;

    do {
        iter1 = .5 * sigma_0 * exp(-1 * r / R_d) * (-1 * exp(z_i/z_d) - exp(-1 * z_f/z_d) + 2);
        z_f += .001;
        z_i -= .001;
        iter2 = .5 * sigma_0 * exp(-1 * r / R_d) * (-1 * exp(z_i/z_d) - exp(-1 * z_f/z_d) + 2);
    } while (abs(iter2 - iter1) > 1);
    if (iter2 < 0) {
        return 0;
    } else {
        return iter2 / (z_f - z_i);
    }
}

double H1_gas_disc_antiderivative(const double r) {
    if (r == 0) {
        return 0;
    }
    const double sigma_0H = 5.31E7;
    const double R_d = 7;
    const double R_m = 4;
    const double z_d = .085;

    double z_f = 1.3;
    double z_i = -1.3;

    double iter1 = 0;
    double iter2 = 0;

    do {
        iter1 = .5 * sigma_0H * exp(-1*r/R_d - R_m/r) * (tanh(z_f/(2 * z_d)) - tanh(z_i/(2 * z_d)));
        z_f += .001;
        z_i -= .001;
        iter2 = .5 * sigma_0H * exp(-1*r/R_d - R_m/r) * (tanh(z_f/(2 * z_d)) - tanh(z_i/(2 * z_d)));
    } while (abs(iter2 - iter1) > 1);
    if (iter2 < 0) {
        return 0;
    } else {
        return iter2 / (z_f - z_i);
    }
}

double molecular_gas_disc_antiderivative(const double r) {
    if (r == 0) {
        return 0;
    }
    const double sigma_0H = 2.18E9;
    const double R_d = 1.5;
    const double R_m = 12;
    const double z_d = .045;

    double z_f = 1.3;
    double z_i = -1.3;

    double iter1 = 0;
    double iter2 = 0;

    do {
        iter1 = .5 * sigma_0H * exp(-1*r/R_d - R_m/r) * (tanh(z_f/(2 * z_d)) - tanh(z_i/(2 * z_d)));
        z_f += .001;
        z_i -= .001;
        iter2 = .5 * sigma_0H * exp(-1*r/R_d - R_m/r) * (tanh(z_f/(2 * z_d)) - tanh(z_i/(2 * z_d)));
    } while (abs(iter2 - iter1) > 1);
    if (iter2 < 0) {
        return 0;
    } else {
        return iter2 / (z_f - z_i);
    }
}

double integrate_bulge(const double r) {
    const double step_size = .001;
    double pos_integral = bulge(r, 0);
    int iterations = 0;
    double z = 0;
    while (bulge(r, z) > 1 || iterations % 2 == 0) {
        z += step_size;
        if (iterations % 2 == 0) {
            pos_integral += 4 * bulge(r, z);
        } else {
            pos_integral += 2 * bulge(r, z);
        }
        iterations++;
    }
    pos_integral += bulge(r, z + step_size);
    pos_integral *= step_size / 3;
    pos_integral /= z;

    double neg_integral = bulge(r, 0);
    iterations = 0;
    z = 0;
    while (bulge(r, z) > 1 || iterations % 2 == 0) {
        z -= step_size;
        if (iterations % 2 == 0) {
            neg_integral += 4 * bulge(r, z);
        } else {
            neg_integral += 2 * bulge(r, z);
        }
        iterations++;
    }
    neg_integral += bulge(r, z - step_size);
    neg_integral *= step_size / 3;
    neg_integral /= (-1 * z);

    return pos_integral + neg_integral;
}

void new_mass(double r_start, const int r_step, const int i) {
    const double step_size = .001;
    std::ofstream outfile;
    std::string filename = "./Separate Modified Masses/Modified Mass " + std::to_string(i) + ".txt";
    outfile.open(filename);
    double modified_mass = 0;
    do {
        modified_mass = thin_stellar_disc_antiderivative(r_start) + thick_stellar_disc_antiderivative(r_start) +
                               H1_gas_disc_antiderivative(r_start) + molecular_gas_disc_antiderivative(r_start) + integrate_bulge(r_start);
        outfile << r_start << "\t" << modified_mass << std::endl;
        r_start += r_step * step_size;
    } while (modified_mass > 1);
    outfile.close();
}

void concatenate() {
    std::ifstream outfiles[8]{};
    std::ofstream final_out;
    final_out.open("Modified Mass Distribution.txt");
    for (int i = 0; i < 8; i++) {
        std::string filename = "./Separate Modified Masses/Modified Mass " + std::to_string(i) + ".txt";
        outfiles[i].open(filename);
    }

    while (true) {
        bool all_empty = true;
        for (int i = 0; i < 8; i++) {
            std::string line;
            if (getline(outfiles[i], line)) {
                final_out << line << std::endl;
                all_empty = false;
            }
        }
        if (all_empty) {
            break;
        }
    }

    for (int i = 0; i < 8; i++) {
        outfiles[i].close();
    }
    final_out.close();
}

int main() {
    time_t start = time(nullptr);
    std::thread threads[8]{};
    for (int i = 0; i < 8; i++) {
        threads[i] = std::thread(new_mass, i * .001, 8, i);
    }
    std::cout << "Threads set in motion." << std::endl;
    for (int i = 0; i < 8; i++) {
        threads[i].join();
    }
    concatenate();
    std::cout << "Execution Time: " << time(nullptr) - start << " s." << std::endl;
    return 0;
}
