#include "RandomGenerator.h"

RandomGenerator::RandomGenerator(const RandomGenerator& other)
{
	_gen = other._gen;
	_dis = other._dis;
}

void RandomGenerator::operator=(const RandomGenerator& other)
{
	_gen = other._gen;
	_dis = other._dis;
}

RandomGenerator::RandomGenerator(const int& begin, const int& end)
	: _gen(_rd()), _dis(begin, end) {}

int RandomGenerator::NextValue()
{
	return _dis(_gen);
}

void RandomGenerator::SeedData(bool* arr, const int& size)
{
	for (int i = 0; i < size; i++)
		arr[i] = NextValue();
}