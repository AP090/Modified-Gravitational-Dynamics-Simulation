import matplotlib.pyplot as plt
import numpy as np

fileA = []
with open('Modified Mass Distribution.txt') as file:
    fileA = file.readlines()

r = []
mass = []

for i in fileA:
    point = i.split("\t")
    r.append(float(point[0]))
    mass.append(float(point[1]))

fig = plt.figure()
plt.yscale("log")
plt.plot(r, mass, '.-', color="black")
plt.xlabel('Radius [kpc]')
plt.ylabel('Mass Density [$M_{\odot} kpc^{-3}$]')
plt.title("Modified Mass Density of the Milky Way")
plt.grid()
fig.savefig("./Plots/Modified Mass Density.png")

fileA.clear()


with open('Newtonian Galactic Field.txt') as file:
    fileA = file.readlines()

r = []
field = []

iterator = 0
for i in fileA:
    if iterator > 6500:
        break
    point = i.split("\t")
    r.append(float(point[0]))
    field.append(float(point[1]))
    iterator += 1

fig = plt.figure()
plt.yscale("log")
plt.plot(r, field, '.-', color="black")
plt.xlabel('Radius [kpc]')
plt.ylabel('Gravitational Field [$kpc s^{-2}$]')
plt.title("Newtonian Galactic Field")
plt.grid()
fig.savefig("./Plots/Newtonian Galactic Field.png")

fileA.clear()


with open('Percent Difference - Galactic Potentials.txt') as file:
    fileA = file.readlines()

r = []
diff = []

iterator = 0
for i in fileA:
    if iterator > 6500:
        break
    point = i.split("\t")
    r.append(float(point[0]))
    diff.append(float(point[1]))
    iterator += 1

fig = plt.figure()
plt.plot(r, diff, '.-', color="black")
plt.xlabel('Radius [kpc]')
plt.ylabel('% Difference')
plt.title("Percent Difference - Newtonian vs MOND Gravitational Potentials")
plt.grid()
fig.savefig("./Plots/Percent Difference - Galactic Potentials.png")

fileA.clear()


fileB = []
with open('Newtonian Galactic Potential.txt') as file:
    linesA = file.readlines()

with open('MOND Galactic Potential.txt') as file:
    linesB = file.readlines()

radiusN = []
potentialN = []
radiusM = []
potentialM = []

iterator = 0
for i in linesA:
    if iterator > 6500:
        break
    point = i.split("\t")
    radiusN.append(float(point[0]))
    potentialN.append(float(point[1]))
    iterator += 1

iterator = 0
for i in linesB:
    if iterator > 6500:
        break
    point = i.split("\t")
    radiusM.append(float(point[0]))
    potentialM.append(float(point[1]))
    iterator += 1

fig = plt.figure()
plt.plot(radiusN, potentialN, '.-', color="black")
plt.plot(radiusM, potentialM, '.-', color="blue")
plt.xlabel('Radius [kpc]')
plt.ylabel('Gravitational Potential [$kpc^2 s^{-2}$]')
plt.title("The Galactic Potential - Newtonian vs MOND")
plt.legend(["Newtonian", "MOND"])
plt.grid()
fig.savefig("./Plots/The Galactic Potential.png")


def plot(radiusE, speedE, phi_ic):
    fileA = []
    fileB = []
    with open("NewtonianOrbits-" + str(phi_ic) + "kms.txt") as file:
        fileA = file.readlines()[1:]

    with open("MONDOrbits-" + str(phi_ic) + "kms.txt") as file:
        fileB = file.readlines()[1:]

    radiusN = []
    speedN = []
    radiusM = []
    speedM = []

    for i in fileA:
        point = i.split("\t")
        radius = float(point[0])
        if radius != 0:
            radiusN.append(radius)
            speedN.append(float(point[2]) / pow(radius, 2))

    print(radiusN[0])
    print(speedN[0])

    for i in fileB:
        point = i.split("\t")
        radius = float(point[0])
        if radius != 0:
            radiusM.append(radius)
            speedM.append(float(point[2]) / pow(radius, 2))

    fig = plt.figure()
    plt.plot(radiusE, speedE, '.-', color="black")
    #plt.plot([1, 2, 3], [100, 200, 300], '.-', color="blue")
    plt.plot(radiusM, speedM, '.-', color="cyan")
    plt.plot(radiusN, speedN, '.-', color="blue")
    plt.xlabel('Radius [kpc]')
    plt.ylabel('Rotational Speed [$km s^{-1}$]')
    plt.title("Galactic Rotation Curves for $\dot{\phi}$(0) = " + str(phi_ic) + " $km s^{-1}$")
    plt.legend(["Empirical", "MOND", "Newtonian"])
    plt.grid()
    #plt.show()
    fig.savefig("./Plots/GalacticRotationCurves" + str(phi_ic) + ".png")


empirical = []
with open('Empirical Rotation Curve.txt') as file:
    empirical = file.readlines()

r = []
speed = []

for i in empirical:
    point = i.split("\t")
    r.append(float(point[0]))
    speed.append(float(point[1]))

#fig = plt.figure()
fig, ax = plt.subplots(1) 
ax.plot(r, speed)
ax.set_xticks(np.round_(np.linspace(0, max(r), num=20), decimals = 2, out = None), np.round_(np.linspace(0, max(r), num=20), decimals = 2, out = None), rotation=90)
ax.set_yticks(np.round_(np.linspace(0, max(speed), num=15), decimals = 2, out = None), np.round_(np.linspace(0, max(speed), num=15), decimals = 2, out = None), rotation=0)

#ax2.plot(x.astype('str'), y)
plt.plot(r, speed, '.-', color="black")
#plt.xticks(r[::10],  rotation='vertical')
#plt.yticks(speed[::5], rotation='horizontal')
#plt.margins(0.2)
plt.xlabel('Radius [kpc]')
plt.ylabel('Rotational Speed [$km s^{-1}$]')
plt.title("Empirical Rotation Curve for the Milky Way")
plt.grid()
plt.subplots_adjust(bottom=0.18)
plt.subplots_adjust(left=0.15)
#plt.show()
fig.savefig("./Plots/EmpiricalRotationCurve.png")

empirical.clear()


with open('Empirical Rotation Curve.txt') as file:
    empirical = file.readlines()

radiusE = []
speedE = []

for i in empirical:
    point = i.split("\t")
    if float(point[0]) > 6.9:
        break
    radiusE.append(float(point[0]))
    speedE.append(float(point[1]))

plot(radiusE, speedE, 233)
plot(radiusE, speedE, 209.2284)
plot(radiusE, speedE, 125.01)
