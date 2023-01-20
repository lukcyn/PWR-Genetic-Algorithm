#pragma once

#include <vector>

class KnapsackProblem
{
	size_t _itemCount;
	size_t _maxWeight;
	int* _itemWeights;
	int* _itemValues;

	int _bestFit;
	bool* _bestSolution;


public:

	KnapsackProblem();

	KnapsackProblem(const KnapsackProblem& other);
	
	KnapsackProblem(KnapsackProblem&& other) noexcept;
	
	KnapsackProblem(const size_t& itemCount, const size_t& maxWeight, int* itemWeights, int* itemValues);

	void LoadProblem(const size_t& itemCount, const size_t& maxWeight, int* itemWeights, int* itemValues);
	
	KnapsackProblem operator=(const KnapsackProblem& other);

	KnapsackProblem& operator=(KnapsackProblem&& other) noexcept;

	int CalculateFitness(const bool* solution, const size_t& solSize);

	int CalculateFitness(const class Individual& indv);

	~KnapsackProblem();

	size_t GetItemCount() const;
	
	size_t GetMaxWeight() const;

private:

	void ArrayCopy(bool*& container, const size_t& size, const bool* copyFrom);
};