#pragma once
#include <utility>
#include <iostream>
#include "functions.h"
#include "constants.h"
#include "EulerMethod.h"

void TASK1(bool showGraphs) {
	std::pair<double, double> discrepancy;
	std::cout << "TASK 1 START --------------------------------\n\n";

	EulerMethod euler(a, b, x_0, y_0, numberOfIterations, functionX, functionV, pathToFiles);

	std::cout << "Euler_100\n";
	euler.calculate("Euler_100.txt");
	discrepancy = euler.discrepancy("maple_100.txt", "Euler_100.txt", "EulerError_100.txt");
	std::cout << "Euler 100 steps; L2_X: " << discrepancy.first << "\t" <<
		"L2_Y: " << discrepancy.second << "\n\n";

	std::cout << "Euler_1000\n";
	euler.setNumberOfSteps(1000);
	euler.calculate("Euler_1000.txt");
	discrepancy = euler.discrepancy("maple_1000.txt", "Euler_1000.txt", "EulerError_1000.txt");
	std::cout << "Euler 1000 steps; L2_X: " << discrepancy.first << "\t" <<
		"L2_Y: " << discrepancy.second << "\n\n";

	std::cout << "Euler_10000\n";
	euler.setNumberOfSteps(10000);
	euler.calculate("Euler_10000.txt");
	discrepancy = euler.discrepancy("maple_10000.txt", "Euler_10000.txt", "EulerError_10000.txt");
	std::cout << "Euler 10000 steps;  L2_X: " << discrepancy.first << "\t" <<
		"L2_Y: " << discrepancy.second << "\n\n";

	std::cout << "EulerRunge_100\n";
	euler.setNumberOfSteps(100);
	euler.orderBoost("EulerRunge_100.txt");
	discrepancy = euler.discrepancy("maple_100.txt", "EulerRunge_100.txt", "EulerRungeError_100.txt");
	std::cout << "EulerRunge 100 steps;  L2_X: " << discrepancy.first << "\t" <<
		"L2_Y: " << discrepancy.second << "\n\n";

	std::cout << "EulerRunge_1000\n";
	euler.setNumberOfSteps(1000);
	euler.orderBoost("EulerRunge_1000.txt");
	discrepancy = euler.discrepancy("maple_1000.txt", "EulerRunge_1000.txt", "EulerRungeError_1000.txt");
	std::cout << "EulerRunge 1000 steps; L2_X: " << discrepancy.first << "\t" <<
		"L2_Y: " << discrepancy.second << "\n\n";

	std::cout << "EulerRunge_10000\n";
	euler.setNumberOfSteps(10000);
	euler.orderBoost("EulerRunge_10000.txt");
	discrepancy = euler.discrepancy("maple_10000.txt", "EulerRunge_10000.txt", "EulerRungeError_10000.txt");
	std::cout << "EulerRunge 10000 steps; L2_X: " << discrepancy.first << "\t" <<
		"L2_Y: " << discrepancy.second << "\n\n";

	if (showGraphs) {
		euler.drawGraph({ {"X_Euler_100.txt", "X-Euler-100"}, {"X_Euler_1000.txt", "X-Euler-1000"},
			{"X_Euler_10000.txt", "X-Euler-10000"}, {"X_maple_10000.txt", "X-Maple-10000"} },
			"Compare Euler and Maple X", "t", "X");
		euler.drawGraph({ {"V_Euler_100.txt", "V-Euler-100"}, {"V_Euler_1000.txt", "V-Euler-1000"},
	{"V_Euler_10000.txt", "V-Euler-10000"}, {"V_maple_10000.txt", "V-Maple-10000"} },
			"Compare Euler and Maple V", "t", "V");

		euler.drawGraph({ {"X_EulerRunge_100.txt", "X-EulerRunge-100"}, {"X_EulerRunge_1000.txt", "X-EulerRunge-1000"},
			{"X_EulerRunge_10000.txt", "X-EulerRunge-10000"}, {"X_maple_10000.txt", "X-Maple-10000"} },
			"Compare EulerRunge and Maple X", "t", "X");
		euler.drawGraph({ {"V_EulerRunge_100.txt", "V-EulerRunge-100"}, {"V_EulerRunge_1000.txt", "V-EulerRunge-1000"},
	{"V_EulerRunge_10000.txt", "V-EulerRunge-10000"}, {"V_maple_10000.txt", "V-Maple-10000"} },
			"Compare EulerRunge and Maple V", "t", "V");

		euler.drawGraph({ {"X_EulerRungeError_10000.txt", "X-EulerRungeError-10000"},
			{"X_EulerError_10000.txt", "X-EulerError-10000"} }, "Compare EulerRunge and Euler error X",
			"t", "ErrorX");

		euler.drawGraph({ {"V_EulerRungeError_10000.txt", "V-EulerRungeError-10000"},
	{"V_EulerError_10000.txt", "V-EulerError-10000"} }, "Compare EulerRunge and Euler error V",
			"t", "ErrorV");

	}


	std::cout << "TASK 1 END --------------------------------\n\n";
}