#include "BoxRestriction2.h"



BoxRestriction2::BoxRestriction2()
{
}


BoxRestriction2::~BoxRestriction2()
{
}

double BoxRestriction2::restrictFunction(std::vector<double> point)
{
	return 2 - point[0];
}
