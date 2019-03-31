#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <chrono>

namespace Random
{
	static long seed = std::chrono::system_clock::now().time_since_epoch().count();
	
	/// <summary> The random number generator itself. </summary>
	static std::default_random_engine generator(seed);
	
	inline int RandomBetween(const int _min, const int _max) { std::uniform_int_distribution<int> distribution(_min, _max); return distribution(generator); }

	inline float RandomScalar() { std::uniform_int_distribution<int> distribution(0, 100000); return (float)distribution(generator) / 100000.0f; }
}
#endif