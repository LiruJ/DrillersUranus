#ifndef RANDOM_H
#define RANDOM_H

// Utility includes.
#include <random>
#include <chrono>

// Typedef includes.
#include <cmath>

/// <summary> Reprents wrapped functions for easy randomness. </summary>
namespace Random
{
	/// <summary> The seed used for the randomness. </summary>
	static long seed = std::chrono::system_clock::now().time_since_epoch().count();
	
	/// <summary> The random number generator itself. </summary>
	static std::default_random_engine generator(seed);
	
	/// <summary> Gets a random value between the given min and max, inclusive. </summary>
	/// <param name="_min"> The minimum value. </param>
	/// <param name="_max"> The maximum value. </param>
	/// <returns> A random value between the given min and max. </returns>
	inline int32_t RandomBetween(const int32_t _min, const int32_t _max) { std::uniform_int_distribution<int32_t> distribution(_min, _max); return distribution(generator); }

	/// <summary> Gets a random float between <c>0</c> and <c>1</c>. </summary>
	/// <returns> A random float between <c>0</c> and <c>1</c>. </returns>
	inline float_t RandomScalar() { std::uniform_int_distribution<int32_t> distribution(0, 100000); return (float)distribution(generator) / 100000.0f; }
}
#endif