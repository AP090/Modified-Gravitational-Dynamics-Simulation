#include <iostream>
#include <fstream>

int main() {
    std::ifstream first;
    first.open("Newtonian Galactic Potential.txt");
    std::ifstream second;
    second.open("MOND Galactic Potential.txt");

    std::ofstream out;
    out.open("Percent Difference - Galactic Potentials.txt");

    double radiusA = 0;
    double radiusB = 0;
    double potentialA = 0;
    double potentialB = 0;
    double avg = 0;
    int iterator = 0;
    while (first >> radiusA) {
        first >> potentialA;
        second >> radiusB;
        second >> potentialB;

        double diff = std::abs(std::abs(potentialA - potentialB) / ((potentialA + potentialB) / 2));
        diff *= 100;
        out << radiusA << "\t" << diff << std::endl;
        while (iterator < 6500) {
            avg += diff;
            iterator++;
            //std::cout << avg << std::endl;
        }

    }

    std::cout << "Average percent difference up to 6.5 kpc: " << (double)avg / iterator << "%." << std::endl;
    first.close();
    second.close();
    out.close();

    return 0;
}
