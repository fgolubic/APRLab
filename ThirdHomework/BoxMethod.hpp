#pragma once
#include<vector>
#include<random>
#include"GoalFunction.h"
#include"Restriction.h"

/**
	Method that checks if implicit restrictions are satisfied. 
*/
bool isImplicitSatisfied(std::vector<Restriction*> implicit, std::vector<double> x) {

	for (auto& imp : implicit) {

		if (imp->restrictFunction(x) < 0) {

			return false;
		}

	}

	return true;
}

/**
	Method that checks if all explicit restrictions are satisfied.
*/
bool isExplicitSatisfied(std::vector<double> xD, std::vector<double> xG, std::vector<double> x) {

	for (int i = 0; i < x.size(); i++) {

		if (x[i] < xD[i] || x[i] > xG[i]) {

			return false;

		}

	}

	return true;
}

/**
	Moves x1  half way towards x2.
*/
std::vector<double> movePoint(std::vector<double> x1, std::vector<double> x2) {
	
	std::vector<double> newPoint(x1.size());

	for (int i = 0; i < x1.size(); i++) {

		newPoint[i] = 0.5 * (x1[i] + x2[i]);

	}

	return newPoint;
}

/**
	Calculates two worst indexes in simplex.
*/
std::pair<int, int> getTwoWorstIndexes(GoalFunction& fun, std::vector<std::vector<double>>& simplex) {

	double max = fun.function(simplex[0]);
	double max2 = max;
	int h = 0;
	int h2 = 0;

	for (int i = 1; i < simplex.size(); i++) {

		double temp = fun.function(simplex[i]);

		if (temp > max) {

			max2 = max;
			h2 = h;

			max = temp;
			h = i;
		}

	}

	return std::make_pair(h, h2);
}

/**
	Calculates centroid of given simplex.
*/
std::vector<double> getCentroid(std::vector<std::vector<double>> simplex)
{
	std::vector<double> centroid = std::vector<double>();

	for (int i = 0; i < simplex[0].size(); i++) {

		double temp = 0;

		for (int j = 0; j < simplex.size(); j++) {

			temp += simplex[j][i];


		}

		temp /= (simplex.size());

		centroid.push_back(temp);

	}

	return centroid;
}

/**
	Implementation of Box method algorithm.
*/
std::vector<double> boxMethod(std::vector<double> x0, GoalFunction& fun, std::vector<Restriction*>& implicit, std::vector<double> xD, std::vector<double> xG, double alpha, double eps) {

	// Ulazne velicine: X0 (pocetna tocka)
	if (!isExplicitSatisfied(xD, xG, x0)) {

		std::cout << "Explicit restrictions not satisfied! Exiting..." << std::endl;
		return std::vector<double>();

	}

	if (!isImplicitSatisfied(implicit, x0)) {

		std::cout << "Implicit restrictions not satisfied! Exiting..." << std::endl;
		return std::vector<double>();

	}

	std::vector<double> xC = x0;

	std::default_random_engine gen; //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<double> dis(0.0, 1.0);

	double n = x0.size();

	std::vector<std::vector<double>> simplex;

	for (int t = 0; t < 2 * n; t++) // generiranje skupa 2n tocaka
	{
		std::vector<double> simplexElement(n);

		for (int i = 0; i < n; i++) {

			double r = dis(gen);

			simplexElement[i] = xD[i] + r * (xG[i] - xD[i]);// nova tocka je unutar eksplicitnih ogr.
		}



		while (!isImplicitSatisfied(implicit, simplexElement)) {

			simplexElement = movePoint(simplexElement, xC);

		}

		simplex.push_back(simplexElement);

		xC = getCentroid(simplex);

	}

	int divCounter = 0;
	double bestFun = fun.function(xC);
	do
	{
		
		std::pair<int, int> indexes = getTwoWorstIndexes(fun, simplex);
		int h = indexes.first;
		int h2 = indexes.second;

		xC = fun.getCentroid(h, simplex);

		if (fun.function(xC) >= bestFun) {
			divCounter++;
		}
		else {
			bestFun = fun.function(xC);
			divCounter = 0;
		}

		if (divCounter >= 100) {

			std::cout << "Algorithm diverged - no improvement in last 100 iterations!" << std::endl;
			break;
		}


		std::vector<double> xR = fun.reflection(xC, simplex[h], alpha); // refleksija

		for (int i = 0; i < n; i++)
		{

			if (xR[i] < xD[i]) {

				xR[i] = xD[i];

			}
			else if (xR[i] > xG[i]) {

				xR[i] = xG[i];

			}

		}

		while (!isImplicitSatisfied(implicit, xR)) {  // provjeravamo implicitna ogr.

			xR = movePoint(xR, xC);

		}

		if (fun.function(xR) > fun.function(simplex[h2])) // ako je to i dalje najlosija tocka
		{
			xR = movePoint(xR, xC);  // jos jednom pomakni prema Xc

		}

		simplex[h] = xR;

	} while ( !fun.nelderMeadContinuation(simplex, xC, eps));

	return xC;
}

