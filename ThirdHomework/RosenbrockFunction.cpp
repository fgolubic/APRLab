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

std::vector<double> RosenbrockFunction::firstDerivative(std::vector<double> x)
{
	derivativeCalls++;

	std::vector<double> res;

	double x1 = -400 * x[0] * (x[1] - pow(x[0], 2)) - 2 *(1- x[0]);

	double x2 = 200 * (x[1] - pow(x[0], 2));

	res.push_back(x1);
	res.push_back(x2);

	return res;
}

Matrix RosenbrockFunction::hess(std::vector<double> x)
{

	hessianCalls++;

	Matrix h(2,2);

	h[0] = { (-400 * (x[1] - 3 * x[0]*x[0]) + 2), -400 * x[0] };


	h[1]= {(-400 * x[0] ), 200 };



	return h;
}
