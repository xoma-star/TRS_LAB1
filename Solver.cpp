#include "Solver.h"

double Solver::discrepancy(const unsigned numberOfIterations, const double& gridPitch,
	const std::string& fileNameMapleResult, const std::string& fileNameMyResult,
	const std::string& outFile)
{
	std::regex regularForMaple("[\\s]+([^\n]+)");
	std::regex regularForMy("[\\t]+([^\n]+)");
	std::smatch matches;
	std::string line;
	std::ifstream inputFile(fileNameMapleResult);
	std::ofstream outError(outFile);

	double L2Norm = 0.;

	//std::unique_ptr<double[]> timeArray{ new double[numberOfIterations] };
	std::unique_ptr<double[]> resulMapletArray{ new double[numberOfIterations] };

	unsigned count = 0;
	double result;
	double diff;
	if (inputFile.is_open())
	{
		while (getline(inputFile, line))
		{
			if (std::regex_search(line, matches, regularForMaple)) {
				result = std::stod(matches[1].str());
				resulMapletArray[count] = result;
				//std::cout << result << "\n";

			}
			count++;
		}
	}
	else {
		std::cout << fileNameMapleResult << "\t FILE NAME\n";
		std::cout << "file don't open\n";
	}
	inputFile.close();

	inputFile.open(fileNameMyResult);
	count = 0;
	if (inputFile.is_open())
	{
		while (getline(inputFile, line))
		{
			if (std::regex_search(line, matches, regularForMy)) {
				result = std::stod(matches[1].str());
				diff = fabs(result - resulMapletArray[count]);

				L2Norm += diff * diff;
				outError << count * gridPitch << "\t" << diff << "\n";

			}
			count++;
		}
	}
	else {
		std::cout << "file don't open\n";
	}

	inputFile.close();
	outError.close();

	L2Norm = sqrt(L2Norm);

	return L2Norm;
}

void Solver::drawGraph(std::vector<std::pair<std::string, std::string>>&& pathTofiles,
	std::string&& graphName, const std::string path, std::string&& labelX, std::string&& labelY)
{
	std::string lineUsing = "\" using ";
	std::string lineName = " title ";
	std::string lineWith = " with lines ls ";
	std::string ls = " lw 3 ";

	int numLine = 1;
	std::string command = "";

	std::string counter;
	command += "\"" + pathTofiles[0].first + lineUsing + "1:2" + lineName + "\"n = " + pathTofiles[0].second + "\"" + lineWith + "1" + ls;
	for (unsigned i = 1; i < pathTofiles.size(); ++i) {
		command += ", ";
		counter = std::to_string(numLine + 1);
		command += "\"" + pathTofiles[i].first + lineUsing + "1:2" + lineName + "\"n = " + pathTofiles[i].second + "\"" + lineWith + counter + ls;

		numLine++;
	}
	command += ";set term wxt title \"" + graphName + "\"";
	command += ";set xlabel \"" + labelX + "\"";
	command += ";set ylabel \"" + labelY + "\"";

	std::ofstream graphic("file");
	graphic << "cd \"" + path + "\"" << "\n";
	graphic << "plot " << command << "; pause mouse keypress" << "\n";
	graphic.close();
	std::system("gnuplot -persist file");

	graphic.close();
}


void Solver::writeToFile(const double* xResult, const double* vResult, const unsigned& size, const std::string& fileName)
{
	std::ofstream fileToWrite(fileName);


	for (unsigned i = 0; i < size; ++i) {
		fileToWrite << xResult[i] << "\t" << vResult[i] << "\n";
	}
	fileToWrite.close();
}
