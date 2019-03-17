#include "InnerPointFunction.h"



InnerPointFunction::InnerPointFunction(Functions& restrictions, std::vector<double> t)
{

	this->restrictions = restrictions;
	this->t = t;

}


InnerPointFunction::~InnerPointFunction()
{
}

double InnerPointFunction::function(std::vector<double> x)
{
	int n = x.size();

	double result = 0.0;
	int i = 0;

	for (auto & g : this->restrictions) {
		i++;

		if (g(x) < 0) {

			result -= t[i - 1] * g(x);

		}

	}

	return result;
}

std::vector<double> InnerPointFunction::firstDerivative(std::vector<double> x)
{
	return std::vector<double>();
}

Matrix InnerPointFunction::hess(std::vector<double> x)
{
	return Matrix();
}


