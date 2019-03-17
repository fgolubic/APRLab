#include "SchaffersFunction.h"



SchaffersFunction::SchaffersFunction(std::vector<double> x0, std::vector<double> xMin, double fMin)
{
}

SchaffersFunction::SchaffersFunction()
{
}


SchaffersFunction::~SchaffersFunction()
{
}

double SchaffersFunction::function(std::vector<double> x)
{
	this->noOfCalls++;

	double a = 0;

	for (int i = 0; i < x.size(); i++) {
		a += pow(x[i], 2);
	}

	double b = sin(sqrt(a) - 0.5);
	double c = pow(1 + 0.001*a, 2);

	return 0.5 + (pow(b, 2) / c);
}
