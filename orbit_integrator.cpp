// To whomever is unfortunate enough to read this good: I know it is the worst thing I have ever written. I am so sorry.
#include <iostream>
#include <fstream>
#include <thread>
#include <cmath>

double kmpersec_to_kpcpergy(double one, bool convert_to_gy) {
    const double conversion_factor = 4.25364;
    if (convert_to_gy) {
        return one / conversion_factor;
    } else {
        return one * conversion_factor;
    }
}

void integrator(double radius, const double phi_velocity, double &final_radius, double &final_r_momentum, double &final_phi_momentum, const double potential[], bool Newtonian) {
    const double m = 1;
    const double danger_threshold = 6.5;
    const double max_time = 5;
    const double delta_t = .00001;
    const double h = .001;
    double t = 0;
    double phi = 0;
    double r_momentum = 0;
    double phi_momentum = m * radius * radius * kmpersec_to_kpcpergy(phi_velocity, true);

    std::ofstream orbits;
    if (Newtonian && phi_velocity == 233) {
        orbits.open("./Orbits/Newtonian/v = 233/Orbit - " + std::to_string(radius) + ", " + std::to_string(phi_momentum) + ".txt");
    } else if (Newtonian && phi_velocity == 209.2284) {
        orbits.open("./Orbits/Newtonian/v = 209.2284/Orbit - " + std::to_string(radius) + ", " + std::to_string(phi_momentum) + ".txt");
    } else if (Newtonian && phi_velocity == 125.01) {
        orbits.open("./Orbits/Newtonian/v = 125.01/Orbit - " + std::to_string(radius) + ", " + std::to_string(phi_momentum) + ".txt");
    } else if (!Newtonian && phi_velocity == 233) {
        orbits.open("./Orbits/MOND/v = 233/Orbit - " + std::to_string(radius) + ", " + std::to_string(phi_momentum) + ".txt");
    } else if (!Newtonian && phi_velocity == 209.2284) {
        orbits.open("./Orbits/MOND/v = 209.2284/Orbit - " + std::to_string(radius) + ", " + std::to_string(phi_momentum) + ".txt");
    } else if (!Newtonian && phi_velocity == 125.01) {
        orbits.open("./Orbits/MOND/v = 125.01/Orbit - " + std::to_string(radius) + ", " + std::to_string(phi_momentum) + ".txt");
    }

    orbits << "t" << "\t" << "r" << "\t" << "phi" << "\t" << "p_r" << "\t" << "p_phi" << std::endl;
    orbits << t << "\t" << radius << "\t" << phi << "\t" << r_momentum << "\t" << phi_momentum << std::endl;
    while (t < max_time) {
        t += delta_t;
        radius = radius + (r_momentum / m) * delta_t;
        phi = phi + (phi_momentum / (m * radius * radius)) * delta_t;
        double effective_radius = 0;
        if (std::abs(radius * 1000 - std::ceil(radius * 1000)) < std::abs(radius * 1000 - std::floor(radius * 1000))) {
            effective_radius = std::ceil(radius * 1000) / 1000;
        } else {
            effective_radius = std::floor(radius * 1000) / 1000;
        }
        if (effective_radius == 0 || effective_radius > danger_threshold) {
            break;
        }
        double finite_diff = (potential[(int)effective_radius * 1000 + 1] - potential[(int)effective_radius * 1000 - 1]) / (2 * h);
        r_momentum = r_momentum + (((phi_momentum * phi_momentum) / (m * radius * radius * radius)) - m * finite_diff) * delta_t;
        phi_momentum = phi_momentum;
        orbits << t << "\t" << radius << "\t" << phi << "\t" << r_momentum << "\t" << phi_momentum << std::endl;
    }
    final_radius = radius;
    final_r_momentum = r_momentum;
    final_phi_momentum = phi_momentum;
    orbits.close();
}

void integration_manager(double r_low, const int r_step, const int i, const double newtonian[], const double mond[]) {
    const double h = .001;
    double m = 1;
    const double danger_threshold = 6;

    /*std::ofstream newton_low;
    std::ofstream newton_avg;
    std::ofstream newton_high;
    std::ofstream mond_low;
    std::ofstream mond_avg;
    std::ofstream mond_high;

    newton_low.open("./FinalData/Newtonian Orbits - " + std::to_string(233) + " km/s " + std::to_string(i) + ".txt");
    newton_avg.open("./FinalData/Newtonian Orbits - " + std::to_string(209.2284) + " km/s " + std::to_string(i) + ".txt");
    newton_high.open("./FinalData/Newtonian Orbits - " + std::to_string(125.01) + " km/s " + std::to_string(i) + ".txt");
    mond_low.open("./FinalData/MOND Orbits - " + std::to_string(233) + " km/s " + std::to_string(i) + ".txt");
    mond_avg.open("./FinalData/MOND Orbits - " + std::to_string(209.2284) + " km/s " + std::to_string(i) + ".txt");
    mond_high.open("./FinalData/MOND Orbits - " + std::to_string(125.01) + " km/s " + std::to_string(i) + ".txt");

    std::ofstream test;
    test.open("./FinalData/text.txt");*/

    while (r_low <= danger_threshold) {
        std::cout << "Orbit integrator at r = " + std::to_string(r_low) + " kpc of " + std::to_string(danger_threshold) + " kpc." << std::endl;
        double final_vals[6][3]{};
        //double val_a = 0;
        integrator(r_low, 233, final_vals[0][0], final_vals[0][1], final_vals[0][2], newtonian, true);
        integrator(r_low, 209.2284, final_vals[1][0], final_vals[1][1], final_vals[1][2], newtonian, true);
        integrator(r_low, 125.01, final_vals[2][0], final_vals[2][1], final_vals[2][2], newtonian, true);

        integrator(r_low, 233, final_vals[3][0], final_vals[3][1], final_vals[3][2], mond, false);
        integrator(r_low, 209.2284, final_vals[4][0], final_vals[4][1], final_vals[4][2], mond, false);
        integrator(r_low, 125.01, final_vals[5][0], final_vals[5][1], final_vals[5][2],mond, false);

        /*final_vals[0][1] = kmpersec_to_kpcpergy(final_vals[0][1] / m, false);
        final_vals[0][2] = kmpersec_to_kpcpergy(final_vals[0][2] / (m * r_low * r_low), false);
        final_vals[1][1] = kmpersec_to_kpcpergy(final_vals[1][1] / m, false);
        final_vals[1][2] = kmpersec_to_kpcpergy(final_vals[1][2] / (m * r_low * r_low), false);
        final_vals[2][1] = kmpersec_to_kpcpergy(final_vals[2][1] / m, false);
        final_vals[2][2] = kmpersec_to_kpcpergy(final_vals[2][2] / (m * r_low * r_low), false);
        final_vals[3][1] = kmpersec_to_kpcpergy(final_vals[3][1] / m, false);
        final_vals[3][2] = kmpersec_to_kpcpergy(final_vals[3][2] / (m * r_low * r_low), false);
        final_vals[4][1] = kmpersec_to_kpcpergy(final_vals[4][1] / m, false);
        final_vals[4][2] = kmpersec_to_kpcpergy(final_vals[4][2] / (m * r_low * r_low), false);
        final_vals[5][1] = kmpersec_to_kpcpergy(final_vals[5][1] / m, false);
        final_vals[5][2] = kmpersec_to_kpcpergy(final_vals[5][2] / (m * r_low * r_low), false);

        //newton_low << val_a << std::endl;
        test << final_vals[0][0] << std::endl;
        newton_low << final_vals[0][0] << "\t" << final_vals[0][1] << "\t" << final_vals[0][2] << "\t" << sqrt(final_vals[0][1] * final_vals[0][1] + final_vals[0][2] * final_vals[0][2]) << std::endl;
        newton_avg << final_vals[1][0] << "\t" << final_vals[1][1] << "\t" << final_vals[1][2] << "\t" << sqrt(final_vals[1][1] * final_vals[1][1] + final_vals[1][2] * final_vals[1][2]) << std::endl;
        newton_high << final_vals[2][0] << "\t" << final_vals[2][1] << "\t" << final_vals[2][2] << "\t" << sqrt(final_vals[2][1] * final_vals[2][1] + final_vals[2][2] * final_vals[2][2]) << std::endl;
        mond_low << final_vals[3][0] << "\t" << final_vals[3][1] << "\t" << final_vals[3][2] << "\t" << sqrt(final_vals[3][1] * final_vals[3][1] + final_vals[3][2] * final_vals[3][2]) << std::endl;
        mond_avg << final_vals[4][0] << "\t" << final_vals[4][1] << "\t" << final_vals[4][2] << "\t" << sqrt(final_vals[4][1] * final_vals[4][1] + final_vals[4][2] * final_vals[4][2]) << std::endl;
        mond_high << final_vals[5][0] << "\t" << final_vals[5][1] << "\t" << final_vals[5][2] << "\t" << sqrt(final_vals[5][1] * final_vals[5][1] + final_vals[5][2] * final_vals[5][2]) << std::endl;
        //std::cout << final_vals[0][0] << std::endl;*/

        r_low += r_step * h;
    }
    /*newton_low.close();
    newton_avg.close();
    newton_high.close();
    mond_low.close();
    mond_avg.close();
    mond_high.close();*/
}

void concatenate() {
    std::ifstream newton_low_out[100]{};
    std::ifstream newton_avg_out[100]{};
    std::ifstream newton_high_out[100]{};
    std::ifstream mond_low_out[100]{};
    std::ifstream mond_avg_out[100]{};
    std::ifstream mond_high_out[100]{};

    std::ofstream newton_low_final;
    std::ofstream newton_avg_final;
    std::ofstream newton_high_final;
    std::ofstream mond_low_final;
    std::ofstream mond_avg_final;
    std::ofstream mond_high_final;

    newton_low_final.open("Newtonian Orbits - " + std::to_string(233) + " km/s.txt");
    newton_avg_final.open("Newtonian Orbits - " + std::to_string(209.2284) + " km/s.txt");
    newton_high_final.open("Newtonian Orbits - " + std::to_string(125.01) + " km/s.txt");
    mond_low_final.open("MOND Orbits - " + std::to_string(233) + " km/s.txt");
    mond_avg_final.open("MOND Orbits - " + std::to_string(209.2284) + " km/s.txt");
    mond_high_final.open("MOND Orbits - " + std::to_string(125.01) + " km/s.txt");

    mond_low_final << "test" << std::endl;

    for (int i = 0; i < 100; i++) {
        std::cout << "Opening the final files." << std::endl;
        newton_low_out[i].open("./FinalData/Newtonian Orbits - " + std::to_string(233) + " km/s " + std::to_string(i) + ".txt");
        newton_avg_out[i].open("./FinalData/Newtonian Orbits - " + std::to_string(209.2284) + " km/s " + std::to_string(i) + ".txt");
        newton_high_out[i].open("./FinalData/Newtonian Orbits - " + std::to_string(125.01) + " km/s " + std::to_string(i) + ".txt");
        mond_low_out[i].open("./FinalData/MOND Orbits - " + std::to_string(233) + " km/s " + std::to_string(i) + ".txt");
        mond_avg_out[i].open("./FinalData/MOND Orbits - " + std::to_string(209.2284) + " km/s " + std::to_string(i) + ".txt");
        mond_high_out[i].open("./FinalData/MOND Orbits - " + std::to_string(125.01) + " km/s " + std::to_string(i) + ".txt");
    }

    newton_low_final << "t" << "\t" << "r" << "\t" << "p_r" << "\t" << "p_phi" << "\t" << "p" << std::endl;
    newton_avg_final << "t" << "\t" << "r" << "\t" << "p_r" << "\t" << "p_phi" << "\t" << "p" << std::endl;
    newton_high_final << "t" << "\t" << "r" << "\t" << "p_r" << "\t" << "p_phi" << "\t" << "p" << std::endl;
    mond_low_final << "t" << "\t" << "r" << "\t" << "p_r" << "\t" << "p_phi" << "\t" << "p" << std::endl;
    mond_avg_final << "t" << "\t" << "r" << "\t" << "p_r" << "\t" << "p_phi" << "\t" << "p" << std::endl;
    mond_high_final << "t" << "\t" << "r" << "\t" << "p_r" << "\t" << "p_phi" << "\t" << "p" << std::endl;

    while (true) {
        bool all_empty = true;
        for (int i = 0; i < 100; i++) {
            std::string line;
            if (getline(newton_low_out[i], line)) {
                newton_low_final << line << std::endl;
                all_empty = false;
            }
        }

        for (int i = 0; i < 100; i++) {
            std::string line;
            if (getline(newton_avg_out[i], line)) {
                newton_avg_final << line << std::endl;
                all_empty = false;
            }
        }

        for (int i = 0; i < 100; i++) {
            std::string line;
            if (getline(newton_high_out[i], line)) {
                newton_high_final << line << std::endl;
                all_empty = false;
            }
        }

        for (int i = 0; i < 100; i++) {
            std::string line;
            if (getline(mond_low_out[i], line)) {
                mond_low_final << line << std::endl;
                all_empty = false;
            }
        }

        for (int i = 0; i < 100; i++) {
            std::string line;
            if (getline(mond_avg_out[i], line)) {
                mond_avg_final << line << std::endl;
                all_empty = false;
            }
        }

        for (int i = 0; i < 100; i++) {
            std::string line;
            if (getline(mond_high_out[i], line)) {
                mond_high_final << line << std::endl;
                all_empty = false;
            }
        }

        if (all_empty) {
            break;
        }
    }

    for (int i = 0; i < 100; i++) {
        newton_low_out[i].close();
        newton_avg_out[i].close();
        newton_high_out[i].close();
        mond_low_out[i].close();
        mond_avg_out[i].close();
        mond_high_out[i].close();
    }
    newton_low_final.close();
    newton_avg_final.close();
    newton_high_final.close();
    mond_low_final.close();
    mond_avg_final.close();
    mond_high_final.close();
}

int main() {
    time_t start = time(nullptr);

    std::ifstream Newtonian;
    std::ifstream MOND;
    Newtonian.open("Newtonian Galactic Field.txt");
    MOND.open("MOND Galactic Potential.txt");
    const double danger_threshold = 6.5;
    double newtonian_potential[(int)danger_threshold * 1000]{};
    double mond_potential[(int)danger_threshold * 1000]{};

    for (int i = 0; i < (int)danger_threshold * 1000; i++) {
        double radiusA = 0;
        double radiusB = 0;
        Newtonian >> radiusA;
        MOND >> radiusB;

        Newtonian >> newtonian_potential[i];
        MOND >> mond_potential[i];
    }

    int thread_number = 100;
    std::thread threads[thread_number]{};
    for (int i = 0; i < thread_number; i++) {
        threads[i] = std::thread(integration_manager, i * .001, 100, i, newtonian_potential, mond_potential);
    }
    std::cout << "Threads set in motion." << std::endl;
    for (int i = 0; i < thread_number; i++) {
        threads[i].join();
    }
    //concatenate();
    std::cout << "Execution Time: " << time(nullptr) - start << " s." << std::endl;
    return 0;
}
