#include "EulerMethod.h"

EulerMethod::EulerMethod(const double& a, const double& b, const double& initialConditionalX,
	const double& initialConditionalY, const unsigned& numberOfIterations,
	const std::function<double(double)> functionDxDt, const std::function<double(double)> functionDvDt, const std::string& path) :
	GaussSolver(a, b, initialConditionalX, initialConditionalY, numberOfIterations, functionDxDt, functionDvDt, path)
{
}
void  EulerMethod::calculate(const std::string& fileName)
{
	//std::cout << "initialConditionalX: " << initialConditionalX << "\n" << "initialConditionalY: " << initialConditionalY << "\n--------\n\n";

	arrayX[0] = initialConditionalX;
	arrayV[0] = initialConditionalY;
	arrayT[0] = 0;

	//std::cout << arrayX[0] << "\t" << arrayV[0] << "\n";

	for (unsigned i = 1; i <= numberOfIterations; ++i) {
		arrayT[i] = gridPitch * i;
		arrayV[i] = arrayV[i - 1] + gridPitch * functionDvDt(arrayX[i - 1]);
		//std::cout << arrayV[i - 1] << " + " << gridPitch << " * " << functionDvDt(arrayX[i - 1]) << "\n";
		//std::cout << "in function " << arrayX[i - 1] << "\n";
		arrayX[i] = arrayX[i - 1] + gridPitch * functionDxDt(arrayV[i - 1]);
		//std::cout << arrayX[i] << "\t" << arrayV[i] << "\n";
		//std::cout << "------------\n\n";
	}
	if (!fileName.empty()) {
		saveToFile(fileName);
	}


}

void EulerMethod::orderBoost(const std::string& fileName)
{
	std::unique_ptr<double[]> secondMeshX;
	std::unique_ptr<double[]> secondMeshV;

	std::unique_ptr<double[]> resultX{ new double[numberOfIterations] };
	std::unique_ptr<double[]> resultV{ new double[numberOfIterations] };

	double sigma = (gridPitch / 2) / ((gridPitch / 2) - gridPitch);

	setNumberOfSteps(numberOfIterations * 2);
	calculate();

	secondMeshX = std::move(arrayX);
	secondMeshV = std::move(arrayV);

	setNumberOfSteps(numberOfIterations / 2);

	calculate();



	for (unsigned i = 0; i < numberOfIterations; ++i) {
		resultX[i] = sigma * arrayX[i] + (1. - sigma) * secondMeshX[i * 2];
		resultV[i] = sigma * arrayV[i] + (1. - sigma) * secondMeshV[i * 2];
	}


	if (!fileName.empty()) {
		saveToFile(std::move(resultX), std::move(resultV), std::move(arrayT), numberOfIterations, fileName);
	}


}
