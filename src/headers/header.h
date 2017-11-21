#include <vector>
#include <random>

#ifndef memes
#define memes

// from vars.cpp
extern std::vector<std::vector<std::vector<int>>> spin;
extern double temperature;

// from initializers.cpp
extern std::mt19937 mersenne;
void randomInitialization(std::vector<int> size);

// from engine.cpp
int localEnergy(int x1, int y1, int z1, std::vector<int> size);
void reduceEnergy();

#endif