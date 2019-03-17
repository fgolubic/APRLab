#pragma once
#include"Matrix.h"
#include"Common.h"
#include<cmath>

/**
	Method that implements Runge Kutta method of numerical integration.
	It takes starting point, matrix of system A, free vector b, integration step T and maximum integration step TMax.
	Returns vector of Result structre.
*/
std::vector<Result> RungeKuttaMethod(const Matrix &x0, const Matrix& A, const Matrix &b, double T, double TMax) {

	std::vector<Result> results = std::vector<Result>((int)(ceil(TMax/T) + 1), Result(T, TMax));

	double t = 0;

	Matrix xK(x0);

	int i = 0;

	for (int j = 0; j < xK.getNoOfRows(); j++) {

		results[i].point.push_back(xK[j][0]);
	}

	while (std::abs(TMax - t) > 0.0001 ) {

		Matrix n1 = A * xK + b;
		Matrix n2 = A * (xK + T * 0.5 * n1) + b;
		Matrix n3 = A * (xK + T * 0.5 * n2) + b;
		Matrix n4 = A * (xK + T * n3)  + b;

		xK += (T / 6) * (n1 + 2 * n2 + 2 * n3 + n4);

		t += T;

		

		i++;

		for (int j = 0; j < xK.getNoOfRows(); j++) {

			results[i].point.push_back(xK[j][0]);
		}

		if (t >= TMax) break;
	}

	return results;

}