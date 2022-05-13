#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>

class Solver
{
public:
	static double discrepancy(const unsigned numberOfIterations, const double& gridPitch,
		const std::string& fileNameMapleResult, const std::string& fileNameMyResult,
		const std::string& outFile);

	static void drawGraph(std::vector<std::pair<std::string, std::string>>&& pathTofiles,
		std::string&& graphName, const std::string path, std::string&& labelX, std::string&& labelY);

	static void writeToFile(const double* xResult, const double* vResult, const unsigned& size,
		const std::string& fileName);


private:

};


