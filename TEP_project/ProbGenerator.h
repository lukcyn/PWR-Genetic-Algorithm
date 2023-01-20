#pragma once

#include "RandomGenerator.h"

class ProbGenerator
{
	RandomGenerator _generator;		// Generates values between defined PROB_MIN and PROB_MAX
	static ProbGenerator* _singleton;

protected:
	ProbGenerator();

public:

	ProbGenerator(const ProbGenerator& other) = delete;
	ProbGenerator operator=(const ProbGenerator& other) = delete;

	static ProbGenerator* GetInstance();

	float NextValue();
};