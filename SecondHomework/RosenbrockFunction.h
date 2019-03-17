#pragma once
#include "GoalFunction.h"
class RosenbrockFunction :
	public GoalFunction
{
public:
	RosenbrockFunction(std::vector<double> x0, std::vector<double> xMin, double fMin);
	RosenbrockFunction();
	virtual ~RosenbrockFunction();
	virtual double function(std::vector<double> x);
};

