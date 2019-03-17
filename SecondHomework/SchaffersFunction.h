#pragma once
#include "GoalFunction.h"
class SchaffersFunction :
	public GoalFunction
{
public:
	SchaffersFunction(std::vector<double> x0, std::vector<double> xMin, double fMin);
	SchaffersFunction();
	~SchaffersFunction();
	virtual double function(std::vector<double> x);

};

