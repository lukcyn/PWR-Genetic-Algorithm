#pragma once
#include <utility>
#include "RandomGenerator.h"

class Individual
{
	friend class KnapsackProblem;

	bool* _genome;
	size_t _genomeSize;

	RandomGenerator _indexGenerator;										// Returns values between 0 and (_genomeSize - 1)
	static RandomGenerator _boolGenerator;								// Returns 0 or 1
	static RandomGenerator _probGenerator;								// Returns values between 0 and 10_000

public:
	Individual() = delete;
	
	Individual(const size_t& genomeSize);

	Individual(const Individual& other);
	
	Individual& operator=(const Individual& other);
	
	Individual(Individual&& other) noexcept;

	Individual& operator&&(Individual&& other) noexcept;

	~Individual();

	void Mutate(const float& mutationProb);									// Probability of single gene mutating  
																			// (meaning every gene can mutate, therefore the prob should be low)					

	std::pair<Individual,Individual> Cross(const Individual& other) const;	// Uniform crossing
};