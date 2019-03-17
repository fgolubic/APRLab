#include "GoalFunction.h"


double GoalFunction::function(double x)
{
	std::vector<double> X;
	X.push_back(x);

	return function(X);
}

void GoalFunction::getUnimodal(double h, double point, double & l, double & r, int dimension , int index )
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

double GoalFunction::goldenCut(double a, double b, double e, int dimension , int index )
{
	int step = 0;
	double k = 0.5 * (sqrt(5)-1);
	double c = b - k * (b - a);
	double d = a + k * (b - a);

	std::vector<double> vecC = std::vector<double>(dimension);
	vecC[index] = c;

	std::vector<double> vecD= std::vector<double>(dimension);
	vecC[index] = d;

	double fc = function(vecC);
	double fd = function(vecD);

	while((b - a) > e) {
		step++;
		if(fc < fd) {
			b = d;
			d = c;
			c = b - k * (b - a);
			fd = fc;
			vecC[index] = c;
			fc = function(vecC);
		} else{
			a = c;
			c = d;
			d = a + k * (b - a);
			fc = fd;
			vecD[index] = d;
			fd = function(vecD);
		}

	

	}
	return (a + b ) / 2; // ili nove vrijednosti a i b
}

double GoalFunction::goldenCut(double point, double e, int dimension , int index )
{
	double l, r;
	getUnimodal(1, point, l, r, dimension, index);
	return goldenCut(l, r, e, dimension, index);
}

void GoalFunction::coordinateSearch(std::vector<double> x0, std::vector<double> e, std::vector<double>& xM)
{
	int iter = 0;
	std::vector<double> x = x0;
	bool flag = true;
	while(flag){
		iter++;
		std::vector<double> xS = x;

		for (int i = 0; i < x.size(); i++) {

			int dimension = x.size();

			x[i] = goldenCut(x[i], e[i], dimension, i);

		}


		for (int i = 0; i < x.size(); i++) {

			if (std::abs(xS[i] - x[i]) <= e[i]) {
				flag = false;
				break;
			}

		}

		
	} 
	xM = x;
}

std::vector<double> GoalFunction::investigate(std::vector<double> xP, std::vector<double> Dx, std::vector<double> e)
{
	std::vector<double> x = xP;

	for (int i = 0; i < xP.size(); i++) {

		double P = function(x);

		x[i] += Dx[i];

		double N = function(x);

		if (N > P) {

			x[i] -= (2 * Dx[i]);

			N = function(x);

			if (N > P) {

				x[i] += Dx[i];
			}

		}

	}

	return x;
}

std::vector<double> GoalFunction::hookeJeeves(std::vector<double> point, std::vector<double> Dx, std::vector<double> e)
{
	std::vector<double> xP = point;
	std::vector<double> xB = point;

	int step = 0;

	std::cout << "Step " << step << " :" << std::endl;
	std::cout << "Point xP :";
	printVector(xP);
	std::cout << "Point xB :";
	printVector(xB);
	std::cout << std::endl;


	do {
		step++;
		std::cout << "Step " << step << " :" << std::endl;

		std::vector<double> xN = investigate(xP, Dx, e);
		double fN = function(xN);
		double fB = function(xB);

		std::cout << "Point xP : ";
		printVector(xP);
		std::cout << "Point xB : ";
		printVector(xB);
		std::cout << "Point xN : ";
		printVector(xN);
		std::cout << "Values of function in xP, xB and xN respectively : " << function(xP) << "  " << fB << "  " << fN<<std::endl;
		std::cout << std::endl;


		if (fN < fB) {
			
			for (int i = 0; i < xP.size(); i++) {

				xP[i] = 2 * xN[i] - xB[i];
			}

			xB = xN;
		}
		else {

			for (int i = 0; i < Dx.size(); i++) {

				Dx[i] /= 2;
			}

			xP = xB;
		}

		
		

	} while (continuation(Dx, e));

	return xB;
}

bool GoalFunction::continuation(std::vector<double> Dx, std::vector<double> e)
{

	for (int i = 0; i < Dx.size(); i++) {

		if (Dx[i] < e[i]) {
			return false;
		}

	}
	return true;
}

std::vector<std::vector<double>> GoalFunction::countSimplex(std::vector<double> X, double offset)
{
	std::vector<std::vector<double>>  simplex = std::vector<std::vector<double>>();

	simplex.push_back(X);

	for (int i = 0; i < X.size(); i++) {
		std::vector<double> temp = X;
		
		temp[i] += offset;

		simplex.push_back(temp);
	}

	return simplex;
}

std::pair<int, int> GoalFunction::getMinMax(std::vector<std::vector<double>> simplex)
{  
	double min = function(simplex[0]);
	double max = function(simplex[0]);
	int h = 0;
	int l = 0;

	for (int i = 0; i < simplex.size(); i++) {

		double temp = function(simplex[i]);

		if ( temp  > max) {
			
			max = temp;
			h = i;
		}

		if( temp < min ){
			
			min = temp;
			l = i;
		}

	}

	return std::make_pair(l,h);
}

std::vector<double> GoalFunction::getCentroid(int h, std::vector<std::vector<double>> simplex)
{
	std::vector<double> centroid = std::vector<double>();

	for (int i = 0; i < simplex[0].size(); i++) {

		double temp = 0;

		for (int j = 0; j < simplex.size(); j++) {

			if (j != h) temp += simplex[j][i];

			
		}
		
		temp /= (simplex.size() - 1 );

		centroid.push_back(temp);

	}

	return centroid;
}

bool GoalFunction::contractionCompare(std::vector<double> xR, std::vector<std::vector<double>> simplex, int h)
{
	double resultXR = function(xR);

	for (int i = 0; i < simplex.size(); i++) {

		if (i == h) continue;

		if (resultXR <= function(simplex[i])) {

			return false;
		}
	}

	return true;
}

void GoalFunction::movePoints(std::vector<std::vector<double>>& simplex, int l, double sigma)
{
	int size = simplex.size();

	for (int i = 0; i < size; i++) {

		if (i == l) continue;

		for (int j = 0; j < simplex[i].size(); j++) {

			simplex[i][j] = sigma * (simplex[i][j] + simplex[l][j]);
		}

	}
}

bool GoalFunction::nelderMeadContinuation(std::vector<std::vector<double>> simplex, std::vector<double> xC, double e)
{
	double resultXC = function(xC);

	double criteriaResult = 0;

	for (int i = 0; i < simplex.size(); i++) {

		criteriaResult += pow((function(simplex[i]) - resultXC), 2);

	}

	criteriaResult /= simplex.size();

	criteriaResult = sqrt(criteriaResult);

	if (criteriaResult > e) return false;

	return true;
}

std::vector<double> GoalFunction::reflection(std::vector<double> xC, std::vector<double> simplexH, double alpha)
{
	std::vector<double> xR = std::vector<double>();

	for (int i = 0; i < xC.size(); i++) {

		xR.push_back((1 + alpha)*xC[i] - alpha * simplexH[i]);

	}
	return xR;
}

std::vector<double> GoalFunction::expansion(std::vector<double> xC, std::vector<double> xR, double gamma)
{
	std::vector<double> xE = std::vector<double>();

	for (int i = 0; i < xC.size(); i++) {

		xE.push_back((1 - gamma)*xC[i] + gamma * xR[i]);

	}
	return xE;
}

std::vector<double> GoalFunction::contraction(std::vector<double> xC, std::vector<double> simplexH, double beta)
{
	std::vector<double> xK = std::vector<double>();

	for (int i = 0; i < xC.size(); i++) {

		xK.push_back((1 - beta)*xC[i] + beta * simplexH[i]);

	}
	return xK;
}

std::vector<double> GoalFunction::nelderMead(std::vector<double> x0, double alpha, double beta, double gamma, double offset, double sigma, double e)
{
	int step = 0;
	std::vector<std::vector<double>> simplex = countSimplex(x0, offset);
	std::vector<double> xC;
	while(true){
		step++;
		std::pair<int,int> minMax = getMinMax(simplex);

		int h = minMax.second;
		int l = minMax.first;

		xC = getCentroid(h, simplex);

		std::cout << " Step " << step << " :" << std::endl;
		std::cout << "Values of xC : ";
		printVector(xC);


		std::vector<double> xR = reflection(xC, simplex[h], alpha);

		if(function(xR) < function(simplex[l]))
		{
			std::vector<double> xE = expansion(xC, xR, gamma);

			if (function(xE) < function(simplex[l])) {

				simplex[h] = xE;
			}
			else {

				simplex[h] = xR;

			}

		}
		else{ 

			if(contractionCompare(xR, simplex, h)) // F(Xr) > F(X[j]) za svaki j = 0..n, j != h
			{     
				
				if (function(xR) < function(simplex[h])) {

					simplex[h] = xR;

				}
				 std::vector<double> xK = contraction(xC, simplex[h], beta);

				 if (function(xK) < function(simplex[h])) {

					 simplex[h] = xK;

				 }
				 else
				 {
					 movePoints(simplex, l, sigma);// pomakni sve tocke prema X[l];

				 }
			}
			else 
			{
				simplex[h] = xR;

			}
		}

		if (nelderMeadContinuation(simplex, xC, e)) break;

	} 
	return xC;
}

void GoalFunction::printVector(std::vector<double> v)
{
	for (int i = 0; i < v.size(); i++) {

		std::cout << v[i] << "   ";

	}

	std::cout << std::endl;
}

std::vector<double> GoalFunction::getX0()
{
	return this->x0;
}

std::vector<double> GoalFunction::getXMin()
{
	return this->xMin;
}

double GoalFunction::getFMin()
{
	return this->fMin;
}

int GoalFunction::getNoOfCalls()
{
	return this->noOfCalls;
}

int GoalFunction::getDerivativeCalls()
{
	return this->derivativeCalls;
}

int GoalFunction::getHessianCalls()
{
	return this->hessianCalls;
}

void GoalFunction::resetNoOfCalls()
{
	this->noOfCalls = 0;
	this->derivativeCalls = 0;
	this->hessianCalls = 0;
}




