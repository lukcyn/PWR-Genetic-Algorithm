#pragma once

#include <fstream>

bool CreateNewTemplate(const char* path);

int* GetValuesFromLine(const std::string& line, size_t& elementCount);

int* GetValuesAssertSize(const std::string& line, const size_t& assertCount);

bool ParseFileToProblem(const char* filePath, class KnapsackProblem& kproblem);