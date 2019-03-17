#pragma once
#include "Restriction.h"
class BoxRestriction1 :
	public Restriction
{
public:
	BoxRestriction1();
	~BoxRestriction1();
	virtual double restrictFunction(std::vector<double> point);
};

