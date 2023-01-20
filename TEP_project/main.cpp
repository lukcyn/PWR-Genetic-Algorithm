#include <iostream>
#include "FileUtils.h"
#include "KnapsackProblem.h"
#include "GeneticAlgorithm.h"
#include "RandomGenerator.h"

#define FILE_PATH "data.txt"

#define POP_SIZE 10

int main()
{
	KnapsackProblem problem;

	if (!ParseFileToProblem(FILE_PATH, problem))
	{
		system("pause");
		return -1;
	}

	
	GeneticAlgorithm ga(POP_SIZE, 0.1f, 0.50f);

	ga.Run(problem);

	system("pause");
	return 0;
}