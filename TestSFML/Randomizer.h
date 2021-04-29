#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <chrono>
#include <random>

class Randomizer
{
public:
	static float random(const int& min, const int& max);
};

#endif