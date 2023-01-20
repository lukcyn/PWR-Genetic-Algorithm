#pragma once

#include <random>

class RandomGenerator
{
	std::random_device _rd;
	std::mt19937 _gen;
	std::uniform_int_distribution<> _dis;

public:
	RandomGenerator() = delete;

	RandomGenerator(const RandomGenerator& other);

	void operator=(const RandomGenerator& other);
	
	RandomGenerator(const int& begin, const int& end);
	
	int NextValue();

	void SeedData(bool* data, const size_t& size);
};