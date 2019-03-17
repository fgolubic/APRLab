#include "ThirdFunction.h"



ThirdFunction::ThirdFunction(std::vector<double> x0, std::vector<double> xMin, double fMin)
{
	this->x0 = x0;
	this->xMin = xMin;
	this->fMin = fMin;
}


ThirdFunction::~ThirdFunction()
{
}

double ThirdFunction::function(std::vector<double> x)
{
	this->noOfCalls++;

	double result = 0;

	for (int i = 0; i < x.size(); i++) {

		result += pow(x[i] - (i + 1), 2);

	}
	return result;
}

ThirdFunction::ThirdFunction()
{
}
