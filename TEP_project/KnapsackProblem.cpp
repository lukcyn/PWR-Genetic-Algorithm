#include "Individual.h"
#include "KnapsackProblem.h"
#include <math.h>

#define DEF_COUNT 0

KnapsackProblem::KnapsackProblem()
{
	_itemCount = DEF_COUNT;
	_maxWeight = DEF_COUNT;
	_itemValues = NULL;
	_itemWeights = NULL;

	_bestFit = DEF_COUNT;
	_bestSolution = NULL;
}

KnapsackProblem::KnapsackProblem(const KnapsackProblem& other)
{
	_itemCount = other._itemCount;
	_maxWeight = other._maxWeight;

	_itemValues = new int[_itemCount];
	_itemWeights = new int[_itemCount];

	for (int i = 0; i < _itemCount; ++i)
	{
		_itemValues[i] = other._itemValues[i];
		_itemWeights[i] = other._itemWeights[i];
	}

	_bestFit = other._bestFit;
	
	if (other._bestSolution != NULL)
	{
		_bestSolution = new bool[_itemCount];
		ArrayCopy(_bestSolution, _itemCount, other._bestSolution);
	}
	else
		_bestSolution = NULL;

}

KnapsackProblem::KnapsackProblem(KnapsackProblem&& other) noexcept
{
	_itemCount = other._itemCount;
	_maxWeight = other._maxWeight;
	_itemValues = other._itemValues;
	_itemWeights = other._itemWeights;
	_bestSolution = other._bestSolution;

	other._itemValues = NULL;
	other._itemWeights = NULL;
	other._bestSolution = NULL;

	_bestFit = -1;
}

KnapsackProblem::KnapsackProblem(const int& itemCount, const int& maxWeight, int* itemWeights, int* itemValues)
{
	LoadProblem(itemCount, maxWeight, itemWeights, itemValues);
}

inline void KnapsackProblem::LoadProblem(const int& itemCount, const int& maxWeight, int* itemWeights, int* itemValues)
{
	delete[] _itemWeights;
	delete[] _itemValues;
	delete[] _bestSolution;

	_maxWeight = abs(maxWeight);
	_itemCount = abs(itemCount);
	_itemWeights = itemWeights;
	_itemValues = itemValues;
	_bestFit = DEF_COUNT;

	// Look if there are any negative numbers
	for (int i = 0; i < itemCount; ++i) 
	{
		_itemWeights[i] = abs(_itemWeights[i]);
		_itemValues[i] = abs(_itemValues[i]);
	}
}

KnapsackProblem KnapsackProblem::operator=(const KnapsackProblem& other)
{
	if (&other == this)
		return *this;

	delete[] _itemValues;
	delete[] _itemWeights;
	delete[] _bestSolution;

	return KnapsackProblem(other);
}

KnapsackProblem& KnapsackProblem::operator=(KnapsackProblem&& other) noexcept
{
	if (&other == this)
		return *this;

	_itemCount = other._itemCount;
	_maxWeight = other._maxWeight;

	delete[] _itemValues;
	_itemValues = other._itemValues;
	other._itemValues = NULL;

	delete[] _itemWeights;
	_itemWeights = other._itemWeights;
	other._itemWeights = NULL;

	delete[] _bestSolution;
	_bestSolution = other._bestSolution;
	other._bestSolution = NULL;

	return *this;
}

int KnapsackProblem::CalculateFitness(const bool* solution, const int& solSize)
{
	if (solSize != _itemCount)
	{
		std::cout << "Solution does not match item count (itemCount/solutionSize) == (" << _itemCount << '/' << solSize << ")" << std::endl;
		return 0;
	}

	int points = 0;
	int totalWeight = 0;

	for (int i = 0; i < _itemCount; ++i)
	{
		bool element = solution[i];

		//Check if element should be put into knapsack
		if (element)
		{
			totalWeight += _itemWeights[i];

			//Add points if capacity is not exceeted. Return 0 otherwise meaning that the fit is terrible.
			if (totalWeight <= _maxWeight)
				points += _itemValues[i];
			else
				return 0;
		
		}
	}
	if (points > _bestFit)
	{
		delete[] _bestSolution;
		_bestSolution = new bool[_itemCount];
		ArrayCopy(_bestSolution, _itemCount, solution);

		_bestFit = points;

		std::cout << "NEW BEST FIT: " << _bestFit << std::endl;
	}

	return points;
}

KnapsackProblem::~KnapsackProblem()
{
	delete[] _itemValues;
	delete[] _itemWeights;
	delete[] _bestSolution;
}

int KnapsackProblem::GetItemCount() const
{
	return _itemCount;
}

int KnapsackProblem::GetMaxWeight() const
{
	return _maxWeight;
}

void KnapsackProblem::PrintBestFit()
{
	if (_bestSolution == NULL)
	{
		std::cout << "No fitting solution found" << std::endl;
		return;
	}

	PrintArray(_itemCount, _bestSolution);
}

void KnapsackProblem::PrintWeights()
{
	PrintArray(_itemCount, _itemWeights);
}

void KnapsackProblem::PrintValues()
{
	PrintArray(_itemCount, _itemValues);
}

void KnapsackProblem::ArrayCopy(bool*& container, const int& size, const bool* copyFrom)
{
	for (int i = 0; i < size; ++i)
		container[i] = copyFrom[i];
}