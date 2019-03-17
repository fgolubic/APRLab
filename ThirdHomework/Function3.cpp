#include "Function3.h"



Function3::Function3()
{
}


Function3::~Function3()
{
}


double Function3::function(std::vector<double> x)
{
	noOfCalls++;

	return pow(x[0] - 2, 2) +  pow(x[1] +3, 2);
}

std::vector<double> Function3::firstDerivative(std::vector<double> x)
{
	derivativeCalls++;

	std::vector<double> result = { 2 * (x[0] - 2), 2 *  (x[1] + 3) };
	return result;
}

Matrix Function3::hess(std::vector<double> x)
{
	hessianCalls;

	Matrix result = Matrix(2, 2);

	result[0][0] = 2;
	result[1][1] = 2;

	return result;
}