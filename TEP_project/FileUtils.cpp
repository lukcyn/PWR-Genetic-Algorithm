#pragma once

#include "FileUtils.h"
#include "KnapsackProblem.h"
#include <iostream>
#include <deque>
#include <sstream>
#include <filesystem>

// Labeled line numbers of input file
// DSC -> line number on which description will be written
// DATA -> line number from which data will be recieved

#define DSC_GENERAL1 0
#define DSC_GENERAL2 1

#define DSC_ITEM_VALUE 3
#define DATA_ITEM_VALUE 4

#define DSC_ITEM_WEIGHT 6
#define DATA_ITEM_WEIGHT 7

#define DSC_BACKPACK_CAPACIY 9
#define DATA_BACKPACK_CAPACIY 10

#define ITEM_EOF 11

 bool CreateNewTemplate(const char* filePath)
{
	std::ofstream  str;
	str.open(filePath, std::ios::out);

	if (!str.good())
	{
		std::cout << "ERROR! Cannot open file to make an template at: " << filePath << std::endl;
		return false;
	}

	for (int i = 0; i < ITEM_EOF; ++i)
	{
		switch (i)
		{
			case DSC_GENERAL1:
				str << "// Make sure that number of item values are equal to the number of item weights." << '\n';
				break;

			case DSC_GENERAL2:
				str << "// Some data might be skipped if this condition is not met." << '\n';
				break;

			case DSC_ITEM_VALUE:
				str << "// Write item values below with a space between each new value" << '\n';
				break;

			case DSC_ITEM_WEIGHT:
				str << "// Write item weights below with a space between each new value" << '\n';
				break;

			case DSC_BACKPACK_CAPACIY:
				str << "// Write below total backpack capacity" << '\n';
				break;

			default:
				str << '\n';
				break;
		}
	}

	str.close();
	return true;
}

int* GetValuesFromLine(const std::string& line, int& elementCount)
{
	std::istringstream iss(line);

	elementCount = 0;
	int temp;
	std::deque<int> container;

	//Add all elements to queue and count elements
	while (iss >> temp)
	{
		++elementCount;
		container.push_back(temp);
	}

	int* values = new int[elementCount];
	
	//Parse deque to array
	for (int i = 0; i < elementCount; ++i)
	{
		values[i] = container.front();
		container.pop_front();
	}

	return values;
}

bool GetValuesAssertSize(const std::string& line, const int& assertCount, int*& memToAlloc)
{
	int elCount = 0;
	memToAlloc = GetValuesFromLine(line, elCount);

	if (elCount != assertCount)
	{
		std::cout << "ASSERTION ERROR: Datasets contain unequal number of elements or the elements have wrong format" << std::endl;
		return false;
	}

	return true;
}

bool CheckEmpty(const std::string& line, const char* path)
{
	if (line.empty())
	{
		std::cout << "ERR: Some of the data might be missing at file: " << path << std::endl;
		return true;
	}
	return false;
}

bool ParseFileToProblem(const char* filePath, KnapsackProblem& kproblem)
{
	std::ifstream  str;
	str.open(filePath, std::ios::out);

	int elemNum = 0;
	int backpackCapacity = 0;
	int* itemValues = NULL;
	int* itemWeights = NULL;

	if (!str.good())
	{
		std::cout << "ERROR! Cannot open file to make an template at: " << filePath << std::endl;

		return false;
	}

	for (int i = 0; i < ITEM_EOF && !str.eof(); ++i)
	{
		std::string line;
		std::getline(str, line);

		switch (i)
		{
			case DATA_ITEM_VALUE:
				if (CheckEmpty(line, filePath))
					return false;

				itemValues = GetValuesFromLine(line, elemNum);
				break;

			case DATA_ITEM_WEIGHT:
				if (CheckEmpty(line, filePath))
					return false;

				if (!GetValuesAssertSize(line, elemNum, itemWeights))
				{
					std::cout << "Error at file: " << filePath << std::endl;
					return false;
				}
				break;

			case DATA_BACKPACK_CAPACIY:
				if (CheckEmpty(line, filePath))
					return false;

				backpackCapacity = std::stoi(line);
				break;

			default:
				break;
		}
	}

	str.close();
	
	kproblem.LoadProblem(elemNum, backpackCapacity, itemWeights, itemValues);
	return true;
}

std::vector<KnapsackProblem> ParseDirectoryToProblem(const char* dirPath)
{
	std::vector<KnapsackProblem> container;
	
	KnapsackProblem kp;
	for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(dirPath))
	{
		if (ParseFileToProblem(entry.path().generic_string().c_str(), kp))
			container.push_back(kp);
	}

	return container;
}

void CreateFileAtPathPrompt(const char* path)
{
	std::cout << "Create new template? y/n" << std::endl;

	char choice = '0';

	while (choice != 'y' && choice != 'n')
	{
		std::cin.ignore(256, '\n');
		choice = std::cin.get();
		std::cout << choice << std::endl;
	}

	if (choice == 'y')
	{
		std::cout
			<< "Creating template file at: " << path << '\n'
			<< "Restart the program once the file is filled." << std::endl;

		CreateNewTemplate(path);
	}
}
