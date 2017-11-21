#include <random>
#include <iostream>
#include <vector>

#include "header.h"

std::random_device mTwistSeed;
std::mt19937 mersenne(mTwistSeed());

void randomInitialization(std::vector<int> size)
{
    // increase max number to increase the number of possible elements
    std::uniform_int_distribution<> elementRange(0, 1);

    spin.resize(size[0]);
    for (int i = 0; i < size[0]; ++i)
    {
        spin[i].resize(size[1]);
        for (int j = 0; j < size[1]; ++j)
        {
            spin[i][j].resize(size[2]);
            for (int k = 0; k < size[2]; ++k)
            {
                if (elementRange(mersenne) == 0)
                {
                    spin[i][j][k] = -1;
                }
                else
                {
                    spin[i][j][k] = 1;
                }
                // std::cout << spin[i][j][k] << std::endl;
            }
        }
    }
}