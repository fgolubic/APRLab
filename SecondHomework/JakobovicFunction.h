#pragma once
#include "GoalFunction.h"
class JakobovicFunction :
	public GoalFunction
{
public:
	JakobovicFunction(std::vector<double> x0, std::vector<double> xMin, double fMin);
	JakobovicFunction();
	~JakobovicFunction();
	virtual double function(std::vector<double> x);
};

