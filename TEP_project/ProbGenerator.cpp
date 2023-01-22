#include "ProbGenerator.h"

#define PROB_MIN 0
#define PROB_MAX 100000
#define PRECISION 1000.0f				// Generator returns integer between PROB_MIN and PROB_MAX and divides the result by PRECISION

ProbGenerator* ProbGenerator::_singleton = NULL;

ProbGenerator::ProbGenerator()
	: _generator(PROB_MIN, PROB_MAX){}

ProbGenerator* ProbGenerator::GetInstance()
{
	if (_singleton != NULL)
		return _singleton;
	
	_singleton = new ProbGenerator();
	return _singleton;
}

float ProbGenerator::NextValue()
{
	return (float)_generator.NextValue()/PRECISION;
}