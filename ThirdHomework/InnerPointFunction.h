#pragma once
#include "GoalFunction.h"
#include<functional>

using Functions = std::vector<std::function<double(const std::vector<double>& x)>>;

/**
	Class implemented for goal function to find point that satisfies all restrictions. 

*/
class InnerPointFunction :
	public GoalFunction
{
public:
	InnerPointFunction(Functions & restrictions, std::vector<double> t);
	~InnerPointFunction();
	virtual double function(std::vector<double> x);
	virtual std::vector<double> firstDerivative(std::vector<double> x);
	virtual Matrix hess(std::vector<double> x);

private:
	Functions restrictions;
	std::vector<double> t;
};


