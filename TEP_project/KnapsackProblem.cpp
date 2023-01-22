#include "Individual.h"
#include "KnapsackProblem.h"

#define ERR_COUNT -1

KnapsackProblem::KnapsackProblem()
{
	_itemCount = ERR_COUNT;
	_maxWeight = ERR_COUNT;
	_itemValues = NULL;
	_itemWeights = NULL;

	_bestFit = ERR_COUNT;
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

	ArrayCopy(_bestSolution, _itemCount, other._bestSolution);
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

KnapsackProblem::KnapsackProblem(const size_t& itemCount, const size_t& maxWeight, int* itemWeights, int* itemValues)
{
	LoadProblem(itemCount, maxWeight, itemWeights, itemValues);
}

inline void KnapsackProblem::LoadProblem(const size_t& itemCount, const size_t& maxWeight, int* itemWeights, int* itemValues)
{
	delete[] _itemWeights;
	delete[] _itemValues;
	delete[] _bestSolution;

	_maxWeight = maxWeight;
	_itemCount = itemCount;
	_itemWeights = itemWeights;
	_itemValues = itemValues;
	_bestFit = -1;
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

int KnapsackProblem::CalculateFitness(const Individual& ind) 
{
	//TODO: encapsulate
	return CalculateFitness(ind._genome, ind._genomeSize);
}

int KnapsackProblem::CalculateFitness(const bool* solution, const size_t& solSize)
{
	if (solSize != _itemCount)
	{
		std::cout << "Solution does not match item count (itemCount/solutionSize) == (" << _itemCount << '/' << solSize << ")" << std::endl;
		return 0;
	}

	int points = 0;
	int totalWeight = 0;

	for (size_t i = 0; i < _itemCount; ++i)
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

size_t KnapsackProblem::GetItemCount() const
{
	return _itemCount;
}

size_t KnapsackProblem::GetMaxWeight() const
{
	return _maxWeight;
}

void KnapsackProblem::PrintBestFit()
{
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

void KnapsackProblem::ArrayCopy(bool*& container, const size_t& size, const bool* copyFrom)
{
	for (int i = 0; i < size; ++i)
		container[i] = copyFrom[i];
}