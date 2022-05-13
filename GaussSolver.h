#pragma once

#include <functional>
#include <memory>
#include <iostream>
#include <string>

#include "Solver.h"



class GaussSolver
{
public:
	GaussSolver(const double& a, const double& b, const double& initialConditionalX, const double& initialConditionalY,
		const unsigned& numberOfIterations, const std::function<double(double)> functionDxDt,
		const std::function<double(double)> functionDvDt, const std::string& path);
	virtual void calculate(const std::string& fileName = "") {};

	void setNumberOfSteps(const int& numberOfIterations);

	void drawGraph(std::vector<std::pair<std::string, std::string>>&& pathTofiles,
		std::string&& graphName, std::string&& labelX, std::string&& labelY);
	std::pair<double, double> discrepancy(const std::string& fileNameMapleResult, const std::string& fileNameMyResult,
		const std::string& outFile);


protected:
	std::function<double(double)> functionDvDt;
	std::function<double(double)> functionDxDt;
	double gridPitch;
	double initialConditionalX;
	double initialConditionalY;
	unsigned numberOfIterations;
	std::unique_ptr<double[]> arrayX;
	std::unique_ptr<double[]> arrayV;
	std::unique_ptr<double[]> arrayT;

	void saveToFile(const std::string& fileName);
	void saveToFile(const std::unique_ptr<double[]> arrayX, const std::unique_ptr<double[]> arrayV,
		const std::unique_ptr<double[]> arrayT, const unsigned& size, const std::string& fileName);

private:
	std::string path_;
	double a_;
	double b_;


};