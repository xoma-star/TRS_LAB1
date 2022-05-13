#pragma once

#include "GaussSolver.h"

class EulerMethod : public GaussSolver
{
public:
	EulerMethod(const double& a, const double& b, const double& initialConditionalX, const double& initialConditionalY, const unsigned& numberOfIterations,
		const std::function<double(double)> functionDxDt, const std::function<double(double)> functionDvDt, const std::string& path);

	virtual void calculate(const std::string& fileName = "") override;


	void orderBoost(const std::string& fileName = "");


private:

};