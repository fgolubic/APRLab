#include<iostream>
#include"RosenbrockFunction.h"
#include"Assigment.h"
#include"Function2.h"
#include"Function3.h"
#include"Function4.h"
#include"GradientDescent.hpp"
#include"NewtonRaphson.hpp"
#include"BoxMethod.hpp"
#include"BoxRestriction1.h"
#include"BoxRestriction2.h"
#include"TransformToBoundless.hpp"

using Functions = std::vector<std::function<double(const std::vector<double>& x)>>;

int main(int argc, char** argv) {
	char a;


	zadatak5();

	std::cin >> a;

	return 0;
}


void zadatak1() {

	Function3 fun;

	std::vector<double> x = {0, 0};

	//without golden search
	std::vector<double> min = GradientDescent(fun, x, 0.000001);

	std::cout << "No golden section: " << min[0] <<", "<<min[1]<<std::endl;


	//withgolden search
	min = GradientDescent(fun, x, 0.000001, true);

	std::cout << "Golden section: " << min[0] << ", " << min[1] << std::endl;



}

void zadatak2() {

	RosenbrockFunction rosFun;
	Function2 fun2;

	std::vector<double> xRos = { -1.9, 2 };
	std::vector<double> x2 = { 0.1, 0.3 };


	//First function 
	std::vector<double> min = GradientDescent(rosFun, xRos, 0.000001, true);

	std::cout << "Banana function (GS): " << min[0] << ", " << min[1] << std::endl;

	std::cout << "No of calculations (GS) (function, derivative, hessian): " << rosFun.getNoOfCalls() << ", " << rosFun.getDerivativeCalls() << ", " << rosFun.getHessianCalls() << std::endl;

	rosFun.resetNoOfCalls();

	min = newtonRaphson(xRos, rosFun, 0.000001, true);

	std::cout << "Banana function (NR): " << min[0] << ", " << min[1] << std::endl;

	std::cout << "No of calculations (NR) (function, derivative, hessian): " << rosFun.getNoOfCalls() << ", " << rosFun.getDerivativeCalls() << ", " << rosFun.getHessianCalls() << std::endl;

	//Second function 
	min = GradientDescent(fun2, x2, 0.000001, true);

	std::cout << "Second function (GS): " << min[0] << ", " << min[1] << std::endl;

	std::cout << "No of calculations (GS) (function, derivative, hessian): " << fun2.getNoOfCalls() << ", " << fun2.getDerivativeCalls() << ", " << fun2.getHessianCalls() << std::endl;

	fun2.resetNoOfCalls();

	min = newtonRaphson(x2, fun2, 0.000001, true);

	std::cout << "Second function (NR): " << min[0] << ", " << min[1] << std::endl;

	std::cout << "No of calculations (NR) (function, derivative, hessian): " << fun2.getNoOfCalls() << ", " << fun2.getDerivativeCalls() << ", " << fun2.getHessianCalls() << std::endl;

}

void zadatak3() {

	RosenbrockFunction rosFun;
	Function2 fun2;

	std::vector<double> xRos = { -1.9, 2 };
	std::vector<double> x2 = { 0.1, 0.3 };

	std::vector<Restriction*> restr = { new BoxRestriction1(), new BoxRestriction2() };
	std::vector<double> xD = { -100, -100 };
	std::vector<double> xG = { 100, 100 };

	std::vector<double> min = boxMethod(xRos, rosFun, restr, xD, xG, 1.3, 0.00001);

	std::cout<<"Banana function min (BOX): "<< min[0] << ", " << min[1] << std::endl;


	min = boxMethod(x2, fun2, restr, xD, xG, 1.3, 0.000001);

	std::cout << "Second function function min (BOX): " << min[0] << ", " << min[1] << std::endl;

}


void zadatak4() {

	RosenbrockFunction rosFun;
	Function2 fun2;

	std::vector<double> xRos = { -1.9, 2 };
	std::vector<double> x2 = { 0.1, 0.3 };

	auto g1 = [&](const std::vector<double> &x) {

		BoxRestriction1 r;

		return r.restrictFunction(x);

	};

	auto g2 = [&](const std::vector<double>& x) {

		BoxRestriction2 r;

		return r.restrictFunction(x);

	};

	std::vector<std::function<double(const std::vector<double>& x)>> restr;

	restr.push_back(g1);
	restr.push_back(g2);

	Functions h;

	std::vector<double> min = TransformToBoundless(xRos, 2, rosFun, restr, h, 0.000001);

	std::cout << "Banana function min (To Boundless): " << min[0] << ", " << min[1] << std::endl;


	min = TransformToBoundless(x2, 2, fun2,restr, h,  0.000001);

	std::cout << "Second function function min (To Boundless): " << min[0] << ", " << min[1] << std::endl;

}

void zadatak5() {


	Function4 fun;

	std::vector<double> x = { 5, 5 };

	auto g1 = [&](const std::vector<double>& x) {

		return 3 - x[0] - x[1];
	};

	auto g2 = [&](const std::vector<double>& x) {

		return 3 +1.5 * x[0] - x[1];
	};

	auto h1 = [&](const std::vector<double>& x) {

	return x[1] -1 ;
	};


	Functions g;
	Functions h;

	g.push_back(g1);
	g.push_back(g2);
	h.push_back(h1);


	std::vector<double> min = TransformToBoundless(x, 2, fun, g, h, 0.000001);

	std::cout << "Fourth function min (To Boundless): " << min[0] << ", " << min[1] << std::endl;

}