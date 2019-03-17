#pragma once
#include "GoalFunction.h"
class Function3 :
	public GoalFunction
{
public:
	Function3();
	~Function3();
	virtual double function(std::vector<double> x);
	virtual std::vector<double> firstDerivative(std::vector<double> x);
	virtual Matrix hess(std::vector<double> x);

};

