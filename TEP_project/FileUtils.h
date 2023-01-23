#pragma once

#include <fstream>
#include <vector>

bool CreateNewTemplate(const char* path);

int* GetValuesFromLine(const std::string& line, int& elementCount);

bool GetValuesAssertSize(const std::string& line, const int& assertCount, int*& memToAlloc);

bool ParseFileToProblem(const char* filePath, class KnapsackProblem& kproblem);		// Parses single file to KnapsackProblem

std::vector<class KnapsackProblem> ParseDirectoryToProblem(const char* dirPath);	// Parses all files in given directory to KnapsackProblem vector. 
																	
void CreateFileAtPathPrompt(const char* path);

bool CheckEmpty(const std::string& line, const char* path);