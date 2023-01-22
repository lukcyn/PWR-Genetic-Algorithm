#include "RandomGenerator.h"
#include "FileUtils.h"
#include "KnapsackProblem.h"
#include "GeneticAlgorithm.h"
#include <iostream>

#define FILE_PATH "data_sets/data.txt"

#define POP_SIZE 10
#define MUTATION_PROB 0.1f
#define CROSS_PROB 0.6f

int main()
{
	KnapsackProblem problem;

	if (!ParseFileToProblem(FILE_PATH, problem))
	{
		system("pause");
		return -1;
	}

	GeneticAlgorithm ga(POP_SIZE, MUTATION_PROB, CROSS_PROB);

	ga.Run(problem);

	system("pause");
	return 0;
}