#pragma once
#include "GoalFunction.h"
class Function2 :
	public GoalFunction
{
public:
	Function2();
	~Function2();
	virtual double function(std::vector<double> x);
	virtual std::vector<double> firstDerivative(std::vector<double> x);
	virtual Matrix hess(std::vector<double> x);

};

