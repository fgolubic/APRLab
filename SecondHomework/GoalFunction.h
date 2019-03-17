#ifndef GOALFUNCTION_H
#define GOALFUNCTION_H

#include<vector>
#include<cmath>
#include<iostream>


class GoalFunction
{
public:
	/**
		Function enables function call with just one dimensional point. Internally it calls virtual function with 1D vector.
	*/
	double function(double x);
	/**
		Every inherited class implements its own function 
	*/
	virtual double function(std::vector<double> x) = 0;
	/**
		Function that returns unimodal interval for a given point.
	*/
	void getUnimodal(double h, double point, double& l, double& r, int dimension = 1, int index = 0);
	/**
		Implementation of golden cut algorithm,
	*/
	double goldenCut(double a, double b, double e, int dimension = 1, int index = 0);

	/**
		Implementation of golden cut algorithm with given point, rather than interval.
		Method internaly calls getUnimodal and then runs algorithm on given interval.
	*/
	double goldenCut(double point, double e, int dimension = 1, int index = 0);
	/**
		Implementation of coordinate search algorithm. Minimizing function is golden cut in one dimension.
	*/
	void coordinateSearch(std::vector<double> x0, std::vector<double> e, std::vector<double>& xM);

	/**
		Implementation of Hooke-Jeeves algorithm.
	*/
	std::vector<double> hookeJeeves(std::vector<double> point, std::vector<double> Dx, std::vector<double> e);

	/**
		Implementation of Nelder and Mead algorithm.
	*/
	std::vector<double> nelderMead(std::vector<double> x0, double alpha, double beta, double gamma, double offset, double sigma, double e);
	/**
		Method used for printing vectors.
	*/
	static void printVector(std::vector<double> v);
	/**
		Getter for x0
	*/
	std::vector<double> getX0();
	/**
		Getter for x minimum
	*/
	std::vector<double> getXMin();

	/**
		Getter for minimum of function
	*/
	double getFMin();

	/**
		Returns no of function calls. 
	*/
	int getNoOfCalls();

	/**
		Resets function calls to zero, so it can be measured in another algorithm.
	*/
	void resetNoOfCalls();

private:
	/**
		Method for investigation of xN in Hooke Jeeves algorithm
	*/
	std::vector<double> investigate(std::vector<double> xP, std::vector<double> Dx, std::vector<double> e);

	/**
		Method that evaluates contiuation criteria for Hooke Jeeves algorithm.
	*/
	bool continuation(std::vector<double> Dx, std::vector<double> e);

	/**
		Method calculates simplex for point X. 
	*/
	std::vector<std::vector<double>> countSimplex(std::vector<double> X, double offset);

	/**
		Method that gets indexes of minimal and maximal evaluation of function over simplex points.
	*/
	std::pair<int, int> getMinMax(std::vector<std::vector<double>> simplex);
	/**
		Calculates centroid from given simplex.
	*/
	std::vector<double> getCentroid(int h, std::vector<std::vector<double>> simplex);
	/**
		Used for comparison clause after contration in Nelder and Mead algorithm.
	*/
	bool contractionCompare(std::vector<double> xR, std::vector<std::vector<double>> simplex, int h);

	/**
		Method that moves points towards point with index l in simplex.
	*/
	void movePoints(std::vector<std::vector<double>>& simplex, int l, double sigma);

	/**
		Evaluation of continuation criteria in Nelder and Mead algorithm
	*/
	bool nelderMeadContinuation(std::vector<std::vector<double>> simplex, std::vector<double> xC, double e);


	/**
		Method for reflection.
	*/
	std::vector<double> reflection(std::vector<double> xC, std::vector<double> simplexH, double alpha);
	/**
		Method for expansion.
	*/
	std::vector<double> expansion(std::vector<double> xC, std::vector<double> xR, double gamma);

	/**
		Method for contraction.
	*/
	std::vector<double> contraction(std::vector<double> xC, std::vector<double> simplexH, double beta);

protected:
	std::vector<double> x0;
	std::vector<double> xMin;
	double fMin;
	int noOfCalls;
	
};



#endif // !