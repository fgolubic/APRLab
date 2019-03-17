#pragma once
#include "GoalFunction.h"
class SecondFunction :
	public GoalFunction
{
public:
	SecondFunction();
	SecondFunction(std::vector<double> x0, std::vector<double> xMin, double fMin);
	~SecondFunction();
	virtual double function(std::vector<double> x);
};

