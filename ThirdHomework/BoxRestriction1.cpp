#include "BoxRestriction1.h"



BoxRestriction1::BoxRestriction1()
{
}


BoxRestriction1::~BoxRestriction1()
{
}

double BoxRestriction1::restrictFunction(std::vector<double> point)
{
	return point[1] - point[0];
}
