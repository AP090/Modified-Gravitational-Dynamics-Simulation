import math
import os

f = open("NewtonianOrbits-" + str(233) + "kms.txt", 'w')
f.write("r" + "\t" + "p_r" + "\t" + "p_phi" + "\t" + "p" + "\n")
for filename in os.listdir("./Orbits/Newtonian/v = 233"):
    g = open("./Orbits/Newtonian/v = 233/" + filename)
    lines = g.read().splitlines()
    point = lines[-1].split("\t")
    f.write(point[1] + "\t" + point[3] + "\t" + point[4] + "\t" + str(math.sqrt(float(point[3]) * float(point[3]) + float(point[4]) * float(point[4]))) + "\n")
f.close()

f = open("NewtonianOrbits-" + str(209.2284) + "kms.txt", 'w')
f.write("r" + "\t" + "p_r" + "\t" + "p_phi" + "\t" + "p")
for filename in os.listdir("./Orbits/Newtonian/v = 209.2284"):
    g = open("./Orbits/Newtonian/v = 209.2284/" + filename)
    lines = g.read().splitlines()
    point = lines[-1].split("\t")
    f.write(point[1] + "\t" + point[3] + "\t" + point[4] + "\t" + str(math.sqrt(float(point[3]) * float(point[3]) + float(point[4]) * float(point[4]))) + "\n")
f.close()

f = open("NewtonianOrbits-" + str(125.01) + "kms.txt", 'w')
f.write("r" + "\t" + "p_r" + "\t" + "p_phi" + "\t" + "p")
for filename in os.listdir("./Orbits/Newtonian/v = 125.01"):
    g = open("./Orbits/Newtonian/v = 125.01/" + filename)
    lines = g.read().splitlines()
    point = lines[-1].split("\t")
    f.write(point[1] + "\t" + point[3] + "\t" + point[4] + "\t" + str(math.sqrt(float(point[3]) * float(point[3]) + float(point[4]) * float(point[4]))) + "\n")
f.close()

f = open("MONDOrbits-" + str(233) + "kms.txt", 'w')
f.write("r" + "\t" + "p_r" + "\t" + "p_phi" + "\t" + "p")
for filename in os.listdir("./Orbits/MOND/v = 233"):
    g = open("./Orbits/MOND/v = 233/" + filename)
    lines = g.read().splitlines()
    point = lines[-1].split("\t")
    f.write(point[1] + "\t" + point[3] + "\t" + point[4] + "\t" + str(math.sqrt(float(point[3]) * float(point[3]) + float(point[4]) * float(point[4]))) + "\n")
f.close()

f = open("MONDOrbits-" + str(209.2284) + "kms.txt", 'w')
f.write("r" + "\t" + "p_r" + "\t" + "p_phi" + "\t" + "p")
for filename in os.listdir("./Orbits/MOND/v = 209.2284"):
    g = open("./Orbits/MOND/v = 209.2284/" + filename)
    lines = g.read().splitlines()
    point = lines[-1].split("\t")
    f.write(point[1] + "\t" + point[3] + "\t" + point[4] + "\t" + str(math.sqrt(float(point[3]) * float(point[3]) + float(point[4]) * float(point[4]))) + "\n")
f.close()

f = open("MONDOrbits-" + str(125.01) + "kms.txt", 'w')
f.write("r" + "\t" + "p_r" + "\t" + "p_phi" + "\t" + "p")
for filename in os.listdir("./Orbits/MOND/v = 125.01"):
    g = open("./Orbits/MOND/v = 125.01/" + filename)
    lines = g.read().splitlines()
    point = lines[-1].split("\t")
    f.write(point[1] + "\t" + point[3] + "\t" + point[4] + "\t" + str(math.sqrt(float(point[3]) * float(point[3]) + float(point[4]) * float(point[4]))) + "\n")
f.close()
