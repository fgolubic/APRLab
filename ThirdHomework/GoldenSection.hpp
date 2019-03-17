#pragma once
#include<functional>
#include<vector>
#include<iostream>

/**
	Function for finding unimodal interval.
*/
void getUnimodal(std::function<double(std::vector<double>)>& function, double h, double point, double & l, double & r, int dimension, int index)
{
	std::vector<double> x = std::vector<double>(dimension);
	x[index] = point;

	int iter = 0;

	l = point - h, r = point + h;
	double m = point;
	double fl, fm, fr;
	unsigned int step = 1;

	fm = function(x);

	std::vector<double> vecL = std::vector<double>(dimension);
	vecL[index] = l;

	fl = function(vecL);

	std::vector<double> vecR = std::vector<double>(dimension);
	vecR[index] = r;

	fr = function(vecR);

	if (fm < fr && fm < fl) {
		std::cout << "Exit with 0 steps." << std::endl;
		return;
	}
	else if (fm > fr)
		do
		{
			iter++;
			l = m;
			m = r;
			fm = fr;
			r = point + h * (step *= 2);

			vecR[index] = r;
			fr = function(vecR);


		} while (fm > fr);
	else
		do
		{
			iter++;

			r = m;
			m = l;
			fm = fl;
			l = point - h * (step *= 2);
			vecL[index] = l;
			fl = function(vecL);

		} while (fm > fl);
}

/**
	Implementation of golden section search.
*/
double goldenCut(std::function<double(std::vector<double>)>& function, double a, double b, double e, int dimension, int index)
{
	int step = 0;
	double k = 0.5 * (sqrt(5) - 1);
	double c = b - k * (b - a);
	double d = a + k * (b - a);

	std::vector<double> vecC = std::vector<double>(dimension);
	vecC[index] = c;

	std::vector<double> vecD = std::vector<double>(dimension);
	vecD[index] = d;

	double fc = function(vecC);
	double fd = function(vecD);

	while ((b - a) > e) {
		step++;
		if (fc < fd) {
			b = d;
			d = c;
			c = b - k * (b - a);
			fd = fc;
			vecC[index] = c;
			fc = function(vecC);
		}
		else {
			a = c;
			c = d;
			d = a + k * (b - a);
			fc = fd;
			vecD[index] = d;
			fd = function(vecD);
		}



	}
	return (a + b) / 2; // ili nove vrijednosti a i b
}

double goldenCut(std::function<double(std::vector<double>)>& function, double point, double e, int dimension, int index)
{
	double l, r;
	getUnimodal(function, 1, point, l, r, dimension, index);
	return goldenCut(function, l, r, e, dimension, index);
}