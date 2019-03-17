#pragma once
#include"GoalFunction.h"
#include"GoldenSection.hpp"

/**
	Implementation of Gradiend Descent.
*/
std::vector<double> GradientDescent(GoalFunction& fun,  std::vector<double>  point, double eps,bool goldenSection = false, int maxIter = 1000) {

	std::vector<double> xOld;
	std::vector<double> xNew = point;

	int iter = 0;
	int divCounter = 0;
	double bestFun = fun.function(xNew);

	do {

		xOld = xNew;
		std::vector<double> derivative = fun.firstDerivative(xOld);

		std::function<double(std::vector<double>)> goldenSectionFunction = [&](std::vector<double> lambda) {

			std::vector<double> res(xOld.size());

			for (int i = 0; i < xOld.size(); i++) {

				res[i] = xOld[i] - lambda[0] * derivative[i];

			}

			return fun.function(res);

		};


		double gamma = goldenSection ? goldenCut(goldenSectionFunction, 1.0, eps, 1, 0) : 1.0;

		for (int i = 0; i < point.size(); i++) {

			xNew[i] = xOld[i] - gamma * derivative[i];
		}

		if (std::abs(fun.function(xNew) - bestFun) <= eps ) {
			divCounter++;
		}
		else {
			divCounter = 0;
			bestFun = fun.function(xNew);
		}

		if (divCounter >= 100) {

			std::cout << "Algorithm diverged - no improvement in last 100 iterations!" << std::endl;
			break;
		}

		++iter;

		double norm = 0;
		for (int i = 0; i < xNew.size(); i++) {

			norm += pow(xNew[i] - xOld[i], 2);

		}

		norm = sqrt(norm);

		if (norm <= eps) {
			break;
		}

	} while (iter <= maxIter);

	return xNew;
}
