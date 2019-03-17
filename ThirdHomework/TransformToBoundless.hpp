#pragma once

#include<vector>
#include<functional>
#include"GoalFunction.h"
#include<cmath>
#include"HookeJeeves.hpp"
#include"InnerPointFunction.h"

using Functions = std::vector<std::function<double(const std::vector<double>& x)>>;

/**
	Calculation of logarithm in implicit restriction.
*/
double logR(double x) {

	return x > 0.0 ? log(x) : -INFINITY;

}

/**
	Calculates distance between 2 vectors.
*/
double distance(std::vector<double> x1, std::vector<double> x2){

	double result = 0;


	for (int i = 0; i < x1.size(); i++) {

		result += pow((x1[i] - x2[i]), 2);

	}

	return sqrt(result);

}

/**
	Method that transforms goal function with given restrictions into new goal functions with included restrictions.
	Method then uses Hooke Jeeves to find minimum.
	If starting point was not inside boundaries it creates new one inside boundaries.
*/
std::vector<double> TransformToBoundless(std::vector<double> x0, double t, GoalFunction& f, Functions& g, Functions& h, double eps) {

	bool isPointOutside = false;
	Functions forInnerPoint;

	for (auto& i : g) {

		if (i(x0) < 0) {

			isPointOutside = true;
			forInnerPoint.insert(forInnerPoint.end(), g.begin(), g.end());
			break;
		}
	}

	for (auto& i : h) {

		if (i(x0) < 0) {

			isPointOutside = true;
			forInnerPoint.insert(forInnerPoint.end(), h.begin(), h.end());
			break;
		}
	}


	if (isPointOutside) {

		InnerPointFunction innerPointFunction(forInnerPoint, std::vector<double>(forInnerPoint.size(), 2));
		std::vector<double> dX(x0.size(), 0.5);
		std::vector<double> e(x0.size(), eps);

		auto func = [&](const std::vector<double>& x) {

			return innerPointFunction.function(x);
		};

		x0 = hookeJeeves(x0, dX, e, func);

		GoalFunction::printVector(x0);
	}


	auto Uxr = [&](const std::vector<double>& x) {

		double sumG = 0;
		double sumH = 0;

		for (const auto& i : g) {

			sumG += logR(i(x));
		}

		for (const auto& i : h) {

			const double hx = i(x);

			sumH += pow(hx,2);

		}

		return f.function(x) - sumG / t + t * sumH;
	};


	std::vector<double> xNew(x0);
	std::vector<double> xOld(xNew);
	int divCounter = 0;
	double bestFun = Uxr(xOld);
	do {
		
		xOld = xNew;
		std::vector<double> dX(xNew.size(), 0.5);
		std::vector<double> e(xNew.size(), eps);

		xNew = hookeJeeves(xNew, dX, e, Uxr);

		if (Uxr(xNew) >= bestFun) {
			divCounter++;
		}
		else {
			divCounter = 0;
			bestFun = Uxr(xNew);
		}

		if (divCounter >= 100) {

			std::cout << "Algorithm diverged - no improvement in last 100 iterations!" << std::endl;
			break;
		}


		t *= 10;

	} while (distance(xOld, xNew) > eps);


	return xNew;
}
