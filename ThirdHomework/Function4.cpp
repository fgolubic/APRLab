#include "Function4.h"



Function4::Function4()
{
}


Function4::~Function4()
{
}

double Function4::function(std::vector<double> x)
{
	noOfCalls++;
	return pow(x[0] - 3, 2) +  pow(x[1], 2);
}

std::vector<double> Function4::firstDerivative(std::vector<double> x)
{
	derivativeCalls++;
	std::vector<double> result = { 2 * (x[0] - 3), 2 * (x[1]) };
	return result;
}

Matrix Function4::hess(std::vector<double> x)
{
	hessianCalls;
	Matrix result = Matrix(2, 2);

	result[0][0] = 2;
	result[1][1] = 2;

	return result;
}
