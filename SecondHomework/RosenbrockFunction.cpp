#include "RosenbrockFunction.h"



RosenbrockFunction::RosenbrockFunction(std::vector<double> x0, std::vector<double> xMin, double fMin)
{
	this->x0 = x0;
	this->xMin = xMin;
	this->fMin = fMin;
}

RosenbrockFunction::RosenbrockFunction()
{
}


RosenbrockFunction::~RosenbrockFunction()
{
}

double RosenbrockFunction::function(std::vector<double> x)
{
	this->noOfCalls++;
	
	double result = 100 * pow((x[1] - pow(x[0], 2)), 2) + pow((1 - x[0]), 2);

	return result;
}
