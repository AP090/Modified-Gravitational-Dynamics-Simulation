import matplotlib.pyplot as plt


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
        radiusN.append(radius)
        speedN.append(float(point[2]) / pow(radius, 2))

    for i in fileB:
        point = i.split("\t")
        radius = float(point[0])
        radiusM.append(radius)
        speedM.append(float(point[2]) / pow(radius, 2))

    fig = plt.figure()
    plt.plot(radiusE, speedE, '.-', color="black")
    plt.plot(radiusN, speedN, '.-', color="blue")
    plt.plot(radiusM, speedM, '.-', color="cyan")
    plt.xlabel('Radius [kpc]')
    plt.ylabel('Rotational Speed [$km s^{-1}$]')
    plt.title("Galactic Rotation Curves for $\dot{\phi}$(0) = " + str(phi_ic) + " $km s^{-1}$")
    plt.legend(["Empirical", "Newtonian", "MOND"])
    plt.grid()
    fig.savefig("./Plots/Galactic Rotation Curves " + str(phi_ic) + ".png")


empirical = []
with open('Empirical Rotation Curve.txt') as file:
    empirical = file.readlines()

r = []
speed = []

for i in empirical:
    point = i.split("\t")
    r.append(float(point[0]))
    speed.append(float(point[1]))

fig = plt.figure()
plt.plot(r, empirical, '.-', color="black")
plt.xlabel('Radius [kpc]')
plt.ylabel('Rotational Speed [$km s^{-1}$]')
plt.title("Empirical Rotation Curve for the Milky Way")
plt.grid()
fig.savefig("./Plots/Empirical Rotation Curve.png")

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
