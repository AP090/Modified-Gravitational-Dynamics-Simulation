import matplotlib.pyplot as plt

linesA = []
linesB = []

with open('Newtonian Galactic Potential.txt') as file:
    linesA = file.readlines()

with open('MOND Galactic Potential.txt') as file:
    linesB = file.readlines()

xA = []
yA = []
xB = []
yB = []

for i in linesA:
    point = i.split(" ")
    xA.append(float(point[0]))
    yA.append(float(point[1]))

for i in linesB:
    point = i.split(" ")
    xB.append(float(point[0]))
    yB.append(float(point[1]))

fig = plt.figure()

plt.plot(xA, yA, '.-', color="black")
plt.plot(xB, yB, '.-', color="blue")
plt.xlabel('Radius [kpc]')
plt.ylabel('Gravitational Potential [$kpc^2 s^-2$]')
plt.title("The Galactic Potential")

plt.legend(["Newtonian", "MOND"])
plt.grid()
fig.savefig("Galactic Potential Plot.png")
