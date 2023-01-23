#include "RandomGenerator.h"
#include "ProbGenerator.h"
#include "KnapsackProblem.h"
#include "Individual.h"
#include "GeneticAlgorithm.h"
#include <iostream>
#include <math.h>
#include <vector>

#define MAX_ITERATIONS 500000

GeneticAlgorithm::GeneticAlgorithm(const int& populationSize, float mutationProb, float crossingProb)
	: _indexGenerator(0, populationSize - 1)
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

	_probGenerator = ProbGenerator::GetInstance();
}

void GeneticAlgorithm::Run(KnapsackProblem& judge)
{
	int maxPoints = 0;

	std::vector<Individual> population;

	// Creating initial population
	SeedPopulation(population, _populationSize, judge.GetItemCount());
	
	std::cout 
		<< "Parameters: "
		<< "\nPopulation size:\t" << _populationSize
		<< "\nItem count:\t\t" << judge.GetItemCount()
		<< "\nKnapsack capacity:\t" << judge.GetMaxWeight()
		<< "\nMutation probability:\t" << _mutationProb
		<< "\nCrossing probability:\t" << _crossingProb
		<< "\nEnd condition: iteration count == " << MAX_ITERATIONS 
		<< "\nSIMULATION START" 
		<< std::endl;

	// Simulation itself
	Simulate(population, judge);


	std::cout << "Best fitting individual: " << std::endl;
	judge.PrintBestFit();

	std::cout << "Item weights: " << std::endl;
	judge.PrintWeights();

	std::cout << "Item values: " << std::endl;
	judge.PrintValues();

	std::cout << "SIMULATION COMPLETE!" << std::endl;
}

std::vector<Individual> GeneticAlgorithm::CrossAll(std::vector<Individual>& parents, KnapsackProblem& judge)
{
	std::vector<Individual> children;
	children.reserve(_populationSize);

	int popSizeNow = 0;

	// Begin crossing until desired children count
	while (popSizeNow < _populationSize)
	{
		Individual& p1 = RandomParent(parents, judge);
		Individual& p2 = RandomParent(parents, judge);

		if (_crossingProb > _probGenerator->NextValue())
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
	for (int i = 0; i < _populationSize; ++i)
		population[i].Mutate(_mutationProb);
}

void GeneticAlgorithm::Simulate(std::vector<Individual>& population, KnapsackProblem& judge)
{

	for (int i = 0; i < MAX_ITERATIONS; ++i)
	{
		CalculateAllFitnesses(population, judge);
		population = CrossAll(population, judge);
		Mutate(population);
	}
}

void GeneticAlgorithm::SeedPopulation(std::vector<Individual>& containerToPopulate, const int& indivCount, const int& genomeSize)
{
	containerToPopulate.reserve(indivCount);

	for (int i = 0; i < indivCount; ++i)
		containerToPopulate.emplace_back(genomeSize);
}

Individual& GeneticAlgorithm::RandomParent(std::vector<Individual>& parents, KnapsackProblem& judge)
{
	Individual& p1 = parents[_indexGenerator.NextValue()];
	Individual& p2 = parents[_indexGenerator.NextValue()];

	return p1.CalculateFitness(judge) > p2.CalculateFitness(judge) ? p1 : p2;
}

void GeneticAlgorithm::CalculateAllFitnesses(std::vector<Individual>& population, KnapsackProblem& judge)
{
	for (int i = 0; i < _populationSize; ++i)
		population[i].CalculateFitness(judge);
}
