#pragma once
#include"Matrix.h"
#include"Common.h"
#include<cmath>

/**
	Method that implements Trapezoidal method of numerical integration.
	It takes starting point, matrix of system A, free vector b, integration step T and maximum integration step TMax.
	Returns vector of Result structre.
*/
std::vector<Result> TrapeziodalApproximation(const Matrix &x0, const Matrix &A, const Matrix &b, double T, double TMax){

	int n = A.getNoOfRows();

	std::vector<Result> results = std::vector<Result>((int)(ceil(TMax / T) + 1), Result(T, TMax));

	Matrix C = !(Matrix(n) - T * 0.5 * A);
	Matrix D = C * (Matrix(n) + T * 0.5 * A);

	double t = 0;

	Matrix xK(x0);
	int i = 0;
	for (int j = 0; j < xK.getNoOfRows(); j++) {

		results[i].point.push_back(xK[j][0]);
	}

	while (abs(TMax - t) > 0.00001 ) {

		xK = D * xK + T * 0.5 * C * b;

		t += T;

		

		i++;
		for (int j = 0; j < xK.getNoOfRows(); j++) {

			results[i].point.push_back(xK[j][0]);
		}

		if (t >= TMax) break;
	}

	return results;


}



