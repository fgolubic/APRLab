#include "Function2.h"



Function2::Function2()
{
}


Function2::~Function2()
{
}

double Function2::function(std::vector<double> x)
{
	noOfCalls++;
	return pow(x[0]-4,2) + 4*pow(x[1]-2,2);
}

std::vector<double> Function2::firstDerivative(std::vector<double> x)
{
	derivativeCalls++;
	std::vector<double> result = { 2 * (x[0] - 4), 2 * 4 * (x[1] - 2) };
	return result;
}

Matrix Function2::hess(std::vector<double> x)
{
	hessianCalls++;

	Matrix result = Matrix(2,2);

	result[0][0] = 2;
	result[1][1] = 8;

	return result;
}
