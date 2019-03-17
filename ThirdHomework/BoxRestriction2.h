#pragma once
#include "Restriction.h"
class BoxRestriction2 :
	public Restriction
{
public:
	BoxRestriction2();
	~BoxRestriction2();
	virtual double restrictFunction(std::vector<double> point);
};

