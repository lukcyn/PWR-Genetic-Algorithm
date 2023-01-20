#include "RandomGenerator.h"
#include "KnapsackProblem.h"
#include "Individual.h"
#include "GeneticAlgorithm.h"
#include <iostream>
#include <math.h>
#include <vector>

#define MAX_ITERATIONS 1000

GeneticAlgorithm::GeneticAlgorithm(const int& populationSize, float mutationProb, float crossingProb)
	: _indexGenerator(0, populationSize - 1), _probGenerator(0, 100)
{	
	mutationProb = fabsf(mutationProb);
	crossingProb = fabsf(crossingProb);

	if (populationSize % 2 == 1)
		_populationSize = populationSize + 1;
	else
		_populationSize = populationSize;

	//Assigning and error checking
	_mutationProb = mutationProb > 100 ? 100 : mutationProb;
	_crossingProb = crossingProb > 100 ? 100 : crossingProb;
}

void GeneticAlgorithm::Run(KnapsackProblem& judge)
{
	int maxPoints = 0;

	std::vector<Individual> population;

	// Creating initial population
	SeedPopulation(population, _populationSize, judge.GetItemCount());
	
	std::cout 
		<< "SIMULATION START"
		<< "\nParameters: "
		<< "\nPopulation size:\t" << _populationSize
		<< "\nItem count:\t\t" << judge.GetItemCount()
		<< "\nKnapsack capacity:\t" << judge.GetMaxWeight()
		<< "\nMutation probability:\t" << _mutationProb
		<< "\nCrossing probability:\t" << _crossingProb
		<< "\nEnd condition: iteration count == " << MAX_ITERATIONS << std::endl;

	// Simulation itself
	Simulate(population, judge);

	std::cout << "SIMULATION COMPLETE!" << std::endl;
}

//TODO: Implement
std::vector<Individual> GeneticAlgorithm::CrossAll(std::vector<Individual>& parents, KnapsackProblem& judge)
{
	std::vector<Individual> children;
	children.reserve(_populationSize);

	size_t popSizeNow = 0;

	// Begin crossing until desired children count
	while (popSizeNow < _populationSize)
	{
		Individual& p1 = RandomParent(parents, judge);
		Individual& p2 = RandomParent(parents, judge);

		if (_crossingProb > (float)_probGenerator.NextValue() / 100)
		{
			std::pair<Individual, Individual> pair = p1.Cross(parents[_indexGenerator.NextValue()]);
			children.push_back(std::move(pair.first));
			children.push_back(std::move(pair.second));
		}
		else {
			children.push_back(p1);
			children.push_back(p2);
		}

		popSizeNow += 2;
	}

	return children;
}

void GeneticAlgorithm::Mutate(std::vector<Individual>& population)
{
	for (size_t i = 0; i < _populationSize; ++i)
		population[i].Mutate(_mutationProb);
}

//TODO: Implement
void GeneticAlgorithm::Simulate(std::vector<Individual>& population, KnapsackProblem& judge)
{

	for (int i = 0; i < MAX_ITERATIONS; ++i)
	{
		CalculateAllFitnesses(population, judge);
		population = CrossAll(population, judge);
		Mutate(population);
	}
}

void GeneticAlgorithm::SeedPopulation(std::vector<Individual>& containerToPopulate, const size_t& indivCount, const size_t& genomeSize)
{
	containerToPopulate.reserve(indivCount);

	for (size_t i = 0; i < indivCount; ++i)
		containerToPopulate.emplace_back(genomeSize);
}

Individual& GeneticAlgorithm::RandomParent(std::vector<Individual>& parents, KnapsackProblem& judge)
{
	Individual& p1 = parents[_indexGenerator.NextValue()];
	Individual& p2 = parents[_indexGenerator.NextValue()];

	return judge.CalculateFitness(p1) > judge.CalculateFitness(p2) ? p1 : p2;
}

void GeneticAlgorithm::CalculateAllFitnesses(std::vector<Individual>& population, KnapsackProblem& judge)
{
	for (int i = 0; i < _populationSize; ++i)
		judge.CalculateFitness(population[i]);
}
