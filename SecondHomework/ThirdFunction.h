#pragma once
#include "GoalFunction.h"
class ThirdFunction :
	public GoalFunction
{
public:
	ThirdFunction(std::vector<double> x0, std::vector<double> xMin, double fMin);
	~ThirdFunction();
	virtual double function(std::vector<double> x);
	ThirdFunction();
};

