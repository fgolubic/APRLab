#pragma once
#include"Matrix.h"
#include"GoalFunction.h"
#include<functional>
#include"GoldenSection.hpp"


/**
	Implementation of Newton Raphson algorithm.
*/
std::vector<double> newtonRaphson(std::vector<double> point, GoalFunction& fun, double eps, bool goldenSection = false, int maxIter = 1000 ) {

	Matrix xOld(1,(int)point.size());

	Matrix xNew(1, (int)point.size());

	xNew[0]= point;

	int iter = 0;

	int divCounter = 0;
	double bestFun = fun.function(xNew[0]);

	do {

		xOld = xNew;
		std::vector<double> derivative = fun.firstDerivative(xOld[0]);

		Matrix gradient(1, (int) point.size());
		gradient[0] = derivative;

		Matrix factor = (!fun.hess(xOld[0])) * (~gradient);

		std::function<double(std::vector<double>)> goldenSectionFunction = [&](std::vector<double> lambda) {

			std::vector<double> res(xOld.getNoOfColumns());

			for (int i = 0; i < xOld.getNoOfColumns(); i++) {

				res[i] = xOld[0][i] - lambda[0] * factor[i][0];

			}


			return fun.function(res);
		};

		const double gamma = goldenSection ? goldenCut(goldenSectionFunction, 0, eps, 1, 0) : 1.0;

		for (int i = 0; i < point.size(); i++) {

			xNew[0][i] = xOld[0][i] - gamma * factor[i][0];
		}

		if (fun.function(xNew[0]) >= bestFun) {
			divCounter++;
		}
		else {
			divCounter = 0;
			bestFun = fun.function(xNew[0]);
		}

		if (divCounter >= 100) {

			std::cout << "Algorithm diverged - no improvement in last 100 iterations!" << std::endl;
			break;
		}


		double norm = 0;
		for (int i = 0; i < xNew.getNoOfColumns(); i++) {

			norm += pow(derivative[i], 2);

		}

		norm = sqrt(norm);

		if (norm <= eps) {
			break;
		}

		iter++;

	} while (iter < maxIter);

	return xNew[0];
}