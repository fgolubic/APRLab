#include "SecondFunction.h"



SecondFunction::SecondFunction()
{
}

SecondFunction::SecondFunction(std::vector<double> x0, std::vector<double> xMin, double fMin)
{
	this->x0 = x0;
	this->xMin = xMin;
	this->fMin = fMin;
}

SecondFunction::~SecondFunction()
{
}

double SecondFunction::function(std::vector<double> x)
{
	this->noOfCalls++;


	double result = pow((x[0] - 4), 2) + 4 * pow((x[1] - 2), 2);

	return result;

}
