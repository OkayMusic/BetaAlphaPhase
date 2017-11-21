#include <iostream>
#include <vector>
#include <random>
#include <cmath>

#include "header.h"

int localEnergy(int x1, int y1, int z1, std::vector<int> size)
{
    int energy{0};

    // first we need to implement periodic boundary conditions
    // nearest neighbours to the site x, y, z are the following:
    //
    // x-1, y-1, z+-1
    // x  , y-1, z+-1
    // x-1, y  , z+-1
    // x  ,y   , z+-1
    //
    // SO, if x = 0, we must set [x - 1 = max_x_value]
    // likewise for y
    // likewise for z, but if [z = max_z_value] then [z+1 = 0]
    //
    // here, we denote A = A1, A-1 = A2, A+1 = A3:

    int x2, y2, z2, z3;
    if (x1 == 0)
    {
        x2 = size[0] - 1;
    }
    else
    {
        x2 = x1 - 1;
    }
    if (y1 == 0)
    {
        y2 = size[1] - 1;
    }
    else
    {
        y2 = y1 - 1;
    }
    if (z1 == 0)
    {
        z2 = size[2] - 1;
        z3 = 1;
    }
    else if (z1 == size[2] - 1)
    {
        z2 = z1 - 1;
        z3 = 0;
    }
    else
    {
        z2 = z1 - 1;
        z3 = z1 + 1;
    }

    // now sum the product of the spin at x1, y1, z1 with the spin at each nearest neighbour
    energy += spin[x1][y1][z1] * (
          spin[x2][y2][z2] 
        + spin[x2][y2][z3]
        + spin[x1][y2][z2] 
        + spin[x1][y2][z3] 
        + spin[x2][y1][z2] 
        + spin[x2][y1][z3]
        + spin[x1][y1][z2] 
        + spin[x1][y1][z3]);

    return energy;
}

void wiggle(int x, int y, int z, std::vector<int> size)
{
    int initialSpin = spin[x][y][z];
    int initialEnergy = localEnergy(x, y, z, size);

    // flip the spin and calculate the new energy with the flipped spin state
    spin[x][y][z] = -spin[x][y][z];
    int newEnergy = localEnergy(x, y, z, size);

    // if you've increased the energy flip it back
    // however, there's a chance to keep the crap state if T is high
    std::uniform_real_distribution<> dis(0, 1);
    if (newEnergy >= initialEnergy && 
        std::exp(-(newEnergy - initialEnergy)/temperature) < dis(mersenne))
    {
        spin[x][y][z] = initialSpin;
    }
}

void reduceEnergy()
{
    int xSize = spin.size();
    int ySize = spin[0].size();
    int zSize = spin[0][0].size();

    // this is a more handy way to package the size of the spin array
    std::vector<int> size{xSize, ySize, zSize};

    std::uniform_int_distribution<> xSites(0, xSize - 1);
    std::uniform_int_distribution<> ySites(0, ySize - 1);
    std::uniform_int_distribution<> zSites(0, zSize - 1);

    // now we want to call wiggle once for each site in the system
    // each wiggle should be at a random site
    int numberOfSites = xSize * ySize * zSize;
    for (int i = 0; i < numberOfSites; ++i)
    {
        wiggle(xSites(mersenne), ySites(mersenne), zSites(mersenne), size);
    }
}