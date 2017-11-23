#! /usr/bin/env python
import matplotlib.pyplot as plt


def grabData():
    data = []
    with open("../build/dataFile.dat") as inFile:
        for lines in inFile:
            lines.split(' ')
            data.append(lines)

    return data

if __name__ == "__main__":
    energies = grabData()

    plt.plot(energies)
    plt.show()