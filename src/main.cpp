#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

#include "header.h"

void printSpins(std::vector<int> gridSize)
{
    for (int i = 0; i < gridSize[0]; ++i)
    {
        std::cout << std::endl;
        for (int j = 0; j < gridSize[1]; ++j)
        {
            std::cout << std::endl;
            for (int k = 0; k < gridSize[2]; ++k)
            {
                std::cout << spin[i][j][k];
            }
        }
    }
}

int totalEnergy(std::vector<int> gridSize)
{
    int energy{0};

    for (int i = 0; i < gridSize[0]; ++i)
    {
        for (int j = 0; j < gridSize[1]; ++j)
        {
            for (int k = 0; k < gridSize[2]; ++k)
            {
                energy += localEnergy(i, j, k, gridSize);
            }
        }
    }

    return energy;
}

int runSimulation(std::vector<int> gridSize, double T)
{
    // first initialize the grid to a random configuration
    randomInitialization(gridSize);

    // then set the temperature global variable
    temperature = T;

    // start the simulation
    for (int i = 0; i < 400; ++i)
    {
        reduceEnergy();
    }


    int energy = totalEnergy(gridSize);

    // write to the console
    printSpins(gridSize);
    std::cout << totalEnergy(gridSize) << std::endl;

    // return energy so this can be written to the datafile
    return energy;
}

int main()
{
    // first initialize the grid
    std::vector<int> gridSize{10, 10, 10};

    // open the file in which data will be stored
    std::ofstream dataFile("build/dataFile.dat", std::ofstream::app);
    if (!dataFile.is_open())
    {
        std::cout << "failed to open file";
        exit(1);
    }

    for (int temp = 0; temp < 20; ++temp)
    {
        int energy = runSimulation(gridSize, temp);
        // dataFile << "T = " << temp << ": " << energy << std::endl;
        dataFile << energy << std::endl;
    }


    return 0;
}