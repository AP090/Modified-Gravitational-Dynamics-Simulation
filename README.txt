This repo contains all the source code of for Edward Chang and Aryan Prasad's AMATH 271 course project. It is meant to be run on a Linux system (WSL works). 

(Aryan was in charged of numerical computation, Edward was in charged of typesetting in LaTeX and the theory)

Due to time constraints before final exams, we know that the code is  poorly written and disorganized. If we had more time, I would have refactored and restructured everything. Alas, this is what we have.

IMPORTANT: Please do not alter the internal file structure, as file I/O is
tied to the specific structure of the 'Run' folder.

Warning: The LaTeX source code may compile with warnings and potential errors. But the output PDF wile is not affected.

Compiling Instruction:
Most of the code is written in C++. There is a Makefile called 'make' with the compiler commands. You will need to ensure g++ is installed. Furthermore, some of the programs require the C++ library Eigen for solving linear systems. Type 'make' into the terminal to compile these programs. There are also some Python programs, one of which relies on Matplotlib. Ensure Python3 and that library are installed. They have to be run in a specific order as shown. The run commands are in quotes. Again, if we had more time, I would have made a script that runs these automatically.

1. './modified_mass'
Converts the given mass distribution into one that is solely a function of radius. It outputs its final result as a text file in the main folder.

2. './newtonian_field'
Uses the modified mass distribution to find the Newtonian gravitational field of the galaxy, also outputting as an appropriately named file.

3. './modified_source'
Uses the Newtonian field found above to calculate the source term in the MOND version of Poisson's Equation.

4. './newtonian_potential'
Solves for the Newtonian gravitational potential of the galaxy. The system, albeit sparse, is very large, and it can take upwards of 10 minutes to run on a personal computer.

5. './mond_potential'
Solves for the MOND gravitational potential of the galaxy. It also takes upwards of 10 minutes to run.

6. './percent_diff'
Find the percentage difference between Newtonian and MOND gravitational potentials.

7. './orbit_integrator'
Uses the gravitational potentials to find orbits of stars throughout the galaxy. It runs for a very long time scale (~5 galactic years) and uses mulithreading. It was run with 100 threads on the CS Club's high-performance computer and
took a couple minutes. Lowering the variable 'max_time' may be wise. The files it outputs will also consume a lot of 
disk storage.

8. 'python3 concatenator.py'
Finds the final radii and momenta of all the orbits calculted in the previous step and packages them neatly into files used to generate rotation curves. It can also take a few minutes depending on file size generated.

9. 'python3 mass_field_potentials_plot.py'
Plots the mass distribution, Newtonian field, both potentials, the percent difference, and rotation curves, outputting eight graphs in the 'Plots' subfolder.


If you run into any issues, please reach out to us. This all worked on our systems and the UW CS Club HFCS cluster, but technology can be unpredictable. Here are links to install guides in case any of that is not on your system.

Contacts:
Edward Chang: edward.chang@uwaterloo.ca (for questions regarding theory, LaTeX, Linux, UW CSC HFCS)
Aryan Prasad: aryanprasad090@gmail.com (for questions regarding c++, python, numerical methods)

Installing g++: https://linuxhint.com/install-and-use-g-on-ubuntu/
Installing Eigen: https://robots.uc3m.es/installation-guides/install-eigen.html#install-eigen3-ubuntu
Installing Python: https://www.scaler.com/topics/python/install-python-on-linux/
Installing Matplotlib: https://matplotlib.org/stable/users/installing/index.html
