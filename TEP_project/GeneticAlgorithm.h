#pragma once

class GeneticAlgorithm
{
	int _populationSize;
	float _crossingProb;
	float _mutationProb;

	class RandomGenerator _indexGenerator;
	class ProbGenerator* _probGenerator;

public:
	GeneticAlgorithm() = delete;

	GeneticAlgorithm(const int& populationSize, float mutationProb, float crossingProb);

	GeneticAlgorithm(const GeneticAlgorithm& other) = delete;

	GeneticAlgorithm& operator=(const GeneticAlgorithm& other) = delete;

	void Run(class KnapsackProblem& judge);

private:
	std::vector<class Individual> CrossAll(std::vector<class Individual>& parents, class KnapsackProblem& judge);

	void Mutate(std::vector<class Individual>& population);

	void Simulate(std::vector<class Individual>& population, class KnapsackProblem& judge);

	void SeedPopulation(std::vector<class Individual>& containerToPopulate, const int& indivCount, const int& genomeSize);

	class Individual& RandomParent(std::vector<class Individual>& parents, class KnapsackProblem& judge);
	
	void CalculateAllFitnesses(std::vector<class Individual>& population, KnapsackProblem& judge);
};