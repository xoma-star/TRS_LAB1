#include "GaussSolver.h"

GaussSolver::GaussSolver(const double& a,
	const double& b,
	const double& initialConditionalX,
	const double& initialConditionalY,
	const unsigned& numberOfIterations,
	const std::function<double(double)> functionDxDt,
	const std::function<double(double)> functionDvDt,
	const std::string& path) : a_{ a },
	b_{ b },
	functionDxDt{ functionDxDt },
	functionDvDt{ functionDvDt },
	initialConditionalX{ initialConditionalX },
	initialConditionalY{ initialConditionalY },
	numberOfIterations{ numberOfIterations },
	arrayX{ new double[numberOfIterations] },
	arrayV{ new double[numberOfIterations] },
	arrayT{ new double[numberOfIterations] },
	path_{ path }
{
	gridPitch = (double)((a_ + b_) / numberOfIterations);
}

void GaussSolver::setNumberOfSteps(const int& numberOfIterations)
{
	this->numberOfIterations = numberOfIterations;
	gridPitch = (double)((a_ + b_) / numberOfIterations);
	arrayX.reset(new double[numberOfIterations]);
	arrayV.reset(new double[numberOfIterations]);
	arrayT.reset(new double[numberOfIterations]);
}

void GaussSolver::drawGraph(std::vector<std::pair<std::string, std::string>>&& pathTofiles,
	std::string&& graphName, std::string&& labelX, std::string&& labelY)
{
	Solver::drawGraph(std::move(pathTofiles), std::move(graphName), path_, std::move(labelX),
		std::move(labelY));
}

std::pair<double, double> GaussSolver::discrepancy(const std::string& fileNameMapleResult, const std::string& fileNameMyResult, const std::string& outFile)
{
	return { Solver::discrepancy(numberOfIterations, gridPitch, "X_" + fileNameMapleResult, "X_" + fileNameMyResult,
		"X_" + outFile),
	Solver::discrepancy(numberOfIterations, gridPitch, "V_" + fileNameMapleResult, "V_" + fileNameMyResult,
		"V_" + outFile) };
}


void GaussSolver::saveToFile(const std::string& fileName)
{
	Solver::writeToFile(arrayT.get(), arrayX.get(), numberOfIterations, "X_" + fileName);
	Solver::writeToFile(arrayT.get(), arrayV.get(), numberOfIterations, "V_" + fileName);
}

void GaussSolver::saveToFile(const std::unique_ptr<double[]> arrayX, const std::unique_ptr<double[]> arrayV,
	const std::unique_ptr<double[]> arrayT, const unsigned& size, const std::string& fileName)
{
	Solver::writeToFile(arrayT.get(), arrayX.get(), size, "X_" + fileName);
	Solver::writeToFile(arrayT.get(), arrayV.get(), size, "V_" + fileName);
}


