all: modified_mass newtonian_field modified_source newtonian_potential mond_potential orbit_integrator percent_diff

modified_mass: modified_mass.cpp
	g++ -O2 -pthread modified_mass.cpp -o modified_mass

newtonian_field: newtonian_field.cpp
	g++ -O2 newtonian_field.cpp -o newtonian_field

modified_source: modified_source.cpp quartic.h
	g++ -O2 modified_source.cpp quartic.cpp -o modified_source

newtonian_potential: newtonian_potential.cpp
	g++ -O2 newtonian_potential.cpp -o newtonian_potential

mond_potential: mond_potential.cpp
	g++ -O2 mond_potential.cpp -o mond_potential

orbit_integrator: orbit_integrator.cpp
	g++ -O2 -pthread orbit_integrator.cpp -o orbit_integrator

percent_diff: percent_diff.cpp
	g++ -O2 percent_diff.cpp -o percent_diff