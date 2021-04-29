#include "Randomizer.h"

float Randomizer::random(const int& min, const int& max)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 rng(seed);
	std::uniform_int_distribution<int> gen(min, max);

	return (float)gen(rng);
}