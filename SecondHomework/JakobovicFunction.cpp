#include "JakobovicFunction.h"



JakobovicFunction::JakobovicFunction(std::vector<double> x0, std::vector<double> xMin, double fMin)
{
	this->x0 = x0;
	this->xMin = xMin;
	this->fMin = fMin;
}

JakobovicFunction::JakobovicFunction()
{
}


JakobovicFunction::~JakobovicFunction()
{
}

double JakobovicFunction::function(std::vector<double> x)
{
	this->noOfCalls++;

	double a = std::abs((x[0] - x[1]) * (x[0] + x[1]));
	double b = sqrt(pow(x[0],2) + pow(x[1],2));
	return a + b;
}
