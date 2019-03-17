#pragma once
#include<vector>

/**
	Struct used to store steps of numerical integration.
	T -> integration step
	TMax -> maximum integration step
	Former two parameters are usually common for every element in Result lists.
	point-> values of a point in a given step.
*/
struct Result {

	Result(double T, double TMax);

	double T;
	double TMax;
	std::vector<double> point;
};

/**
	Method writes Results in file given by filename.
	In first line of a file it writes T and TMax.
	Every other line contains point (n x double values) in a given step of integration.
*/
bool toFile(std::vector<Result> result, std::string fileName);