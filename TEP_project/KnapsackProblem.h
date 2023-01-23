#pragma once

#include <iostream>
#include <vector>

class KnapsackProblem
{
	int _itemCount;
	int _maxWeight;
	int* _itemWeights;
	int* _itemValues;

	int _bestFit;
	bool* _bestSolution;

public:
	KnapsackProblem();

	KnapsackProblem(const KnapsackProblem& other);
	
	KnapsackProblem(KnapsackProblem&& other) noexcept;
	
	KnapsackProblem(const int& itemCount, const int& maxWeight, int* itemWeights, int* itemValues);

	void LoadProblem(const int& itemCount, const int& maxWeight, int* itemWeights, int* itemValues);
	
	KnapsackProblem operator=(const KnapsackProblem& other);

	KnapsackProblem& operator=(KnapsackProblem&& other) noexcept;

	int CalculateFitness(const bool* solution, const int& solSize);

	~KnapsackProblem();

	int GetItemCount() const;
	
	int GetMaxWeight() const;

	void PrintBestFit();

	void PrintWeights();

	void PrintValues();
private:

	template<typename T>
	void PrintArray(const int& size, const T* arr);

	void ArrayCopy(bool*& container, const int& size, const bool* copyFrom);
};

template<typename T>
inline void KnapsackProblem::PrintArray(const int& size, const T* arr)
{
	for (int i = 0; i < size; ++i)
		std::cout << arr[i] << " ";

	std::cout << std::endl;
}
