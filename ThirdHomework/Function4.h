#pragma once
#include "GoalFunction.h"
class Function4 :
	public GoalFunction
{
public:
	Function4();
	~Function4();

	virtual double function(std::vector<double> x);
	virtual std::vector<double> firstDerivative(std::vector<double> x);
	virtual Matrix hess(std::vector<double> x);
};

