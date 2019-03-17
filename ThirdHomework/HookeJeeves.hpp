#pragma once
#include<vector>
#include<functional>

/**
	Investegation part of Hooke Jeeves algorithm.
*/
std::vector<double> investigate(std::vector<double> xP, std::vector<double> Dx, std::vector<double> e,const std::function<double(const std::vector<double> & x)>& function)
{
	std::vector<double> x = xP;

	for (int i = 0; i < xP.size(); i++) {

		double P = function(x);

		x[i] += Dx[i];

		double N = function(x);

		if (N > P) {

			x[i] -= (2 * Dx[i]);

			N = function(x);

			if (N > P) {

				x[i] += Dx[i];
			}

		}

	}

	return x;
}

/**
	Hooke Jeeves contiuation clause.
*/
bool continuation(std::vector<double> Dx, std::vector<double> e)
{

	for (int i = 0; i < Dx.size(); i++) {

		if (Dx[i] < e[i]) {
			return false;
		}

	}
	return true;
}
	/**
		implementation of Hooke Jeeves algorithm.
	*/
std::vector<double> hookeJeeves(std::vector<double> point, std::vector<double> Dx, std::vector<double> e,const std::function<double(const std::vector<double>& x)>& function)
{
	std::vector<double> xP = point;
	std::vector<double> xB = point;

	

	do {

		std::vector<double> xN = investigate(xP, Dx, e, function);
		double fN = function(xN);
		double fB = function(xB);

		
		if (fN < fB) {

			for (int i = 0; i < xP.size(); i++) {

				xP[i] = 2 * xN[i] - xB[i];
			}

			xB = xN;
		}
		else {

			for (int i = 0; i < Dx.size(); i++) {

				Dx[i] /= 2;
			}

			xP = xB;
		}




	} while (continuation(Dx, e));

	return xB;
}


