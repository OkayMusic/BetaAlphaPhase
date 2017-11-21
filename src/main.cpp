#include <iostream>
#include <vector>
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

int main()
{
    // first initialize the grid
    std::vector<int> gridSize{4, 4, 4};
    randomInitialization(gridSize);

    // then set the temperature
    temperature = 0;
    std::cout << totalEnergy(gridSize) << std::endl;

    // then start the simulation
    for (int i = 0; i < 40; ++i)
    {
        reduceEnergy();
    }

    std::cout << totalEnergy(gridSize) << std::endl;

    printSpins(gridSize); 

    return 0;
}