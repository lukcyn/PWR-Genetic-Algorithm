#include "RandomGenerator.h"
#include "FileUtils.h"
#include "KnapsackProblem.h"
#include "GeneticAlgorithm.h"
#include <iostream>

#define DIR_PATH "data_sets"
#define DEF_FILE_PATH "data_sets/template.txt"

#define POP_SIZE 16
#define MUTATION_PROB 0.1f
#define CROSS_PROB 0.6f

int main()
{
	std::vector<KnapsackProblem> problems = ParseDirectoryToProblem(DIR_PATH);

	if (problems.empty()) 
	{
		CreateFileAtPathPrompt(DEF_FILE_PATH);
		return -1;
	}

	GeneticAlgorithm ga(POP_SIZE, MUTATION_PROB, CROSS_PROB);
	for (int i = 0; i < problems.size(); ++i)
	{
		ga.Run(problems[i]);
		std::cout << std::endl;
	}

	system("pause");
	return 0;
}