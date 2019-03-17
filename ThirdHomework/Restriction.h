#pragma once
#include<vector>
class Restriction
{
public:
	/**
		Function that's used for restrictions in Box algorithm.
	*/
	virtual double restrictFunction(std::vector<double> point) = 0;
};

