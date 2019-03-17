#include<iostream>
#include"JakobovicFunction.h"
#include"ThirdFunction.h"
#include"RosenbrockFunction.h"
#include"SchaffersFunction.h"
#include"SecondFunction.h"
#include"Assigment.h"

int main(int argc, char** argv) {
	char a;
	
	zadatak1();
	//zadatak2();
	//zadatak3();
	//zadatak4();
	//zadatak5();
	

	std::cin >> a;

	return 0;
}


void zadatak1() {

	ThirdFunction fun = ThirdFunction();

	std::vector<double> x0;
	x0.push_back(10);
	std::vector<double> Dx;
	Dx.push_back(0.5);
	std::vector<double> e;
	e.push_back(0.00001);


	std::cout << "-------GOLDEN CUT WITH UNIMODAL INTERVAL -----------" << std::endl;
	double min = fun.goldenCut(10, 0.0001);
	std::cout << min << " noOfIter: " << fun.getNoOfCalls() << std::endl;

	std::cout << "-------COORDINATE SEARCH ALGORITHM -----------" << std::endl;
	std::vector<double> xM;
	fun.coordinateSearch(x0, e, xM);
	std::cout << " noOfIter: " << fun.getNoOfCalls() << std::endl;
	GoalFunction::printVector(xM);

	std::cout << "-------HOOKE JEEVES ALGORITHM -----------" << std::endl;
	xM = fun.hookeJeeves(x0, Dx, e);
	std::cout << " noOfIter: " << fun.getNoOfCalls() << std::endl;
	GoalFunction::printVector(xM);

	std::cout << "-------NELDER AND MEAD ALGORITHM -----------" << std::endl;
	xM = fun.nelderMead(x0, 1, 0.5, 2, 1, 0.5, e[0]);
	std::cout << " noOfIter: " << fun.getNoOfCalls() << std::endl;
	GoalFunction::printVector(xM);

}

void zadatak2() {
	
	std::vector<double> nelderAndMeadEval;
	std::vector<double> hookeJeevesEval;
	std::vector<double> coordinateEval;
	std::vector<std::vector<double>> nelderAndMeadMin;
	std::vector<std::vector<double>> hookeJeevesMin;
	std::vector<std::vector<double>> coordinateMin;


	RosenbrockFunction fun1 = RosenbrockFunction();
	std::vector<double> x0 = { -1.9, 2 };
	std::vector<double> e = { 0.000001, 0.000001 };
	std::vector<double> xM;


	fun1.resetNoOfCalls();

	xM = fun1.nelderMead(x0, 1, 0.5, 2, 0.5, 0.5, 0.000001);

	nelderAndMeadEval.push_back(fun1.getNoOfCalls());
	nelderAndMeadMin.push_back(xM);

	fun1.resetNoOfCalls();

	std::vector<double> Dx = { 0.5, 0.5 };
	xM = fun1.hookeJeeves(x0, Dx, e);

	hookeJeevesEval.push_back(fun1.getNoOfCalls());
	hookeJeevesMin.push_back(xM);

	fun1.resetNoOfCalls();

	fun1.coordinateSearch(x0, e, xM);
	coordinateEval.push_back(fun1.getNoOfCalls());
	coordinateMin.push_back(xM);


	SecondFunction fun2 = SecondFunction();
	x0 = { 0.1, 0.3 };

	fun2.resetNoOfCalls();

	xM = fun2.nelderMead(x0, 1, 0.5, 2, 0.5, 0.5, 0.000001);

	nelderAndMeadEval.push_back(fun2.getNoOfCalls());
	nelderAndMeadMin.push_back(xM);

	fun2.resetNoOfCalls();

	Dx = { 0.5, 0.5 };
	xM = fun2.hookeJeeves(x0, Dx, e);

	hookeJeevesEval.push_back(fun2.getNoOfCalls());
	hookeJeevesMin.push_back(xM);

	fun2.resetNoOfCalls();

	fun2.coordinateSearch(x0, e, xM);
	coordinateEval.push_back(fun2.getNoOfCalls());
	coordinateMin.push_back(xM);

	ThirdFunction fun3 = ThirdFunction();
	x0 = { 0,0,0,0,0 };
	e = { 0.000001, 0.000001 , 0.000001 , 0.000001 ,0.000001 };
	fun3.resetNoOfCalls();

	xM = fun3.nelderMead(x0, 1, 0.5, 2, 0.5, 0.5, 0.000001);

	nelderAndMeadEval.push_back(fun3.getNoOfCalls());
	nelderAndMeadMin.push_back(xM);

	fun3.resetNoOfCalls();

	Dx = { 0.5, 0.5, 0.5, 0.5, 0.5 };
	xM = fun3.hookeJeeves(x0, Dx, e);

	hookeJeevesEval.push_back(fun3.getNoOfCalls());
	hookeJeevesMin.push_back(xM);

	fun3.resetNoOfCalls();

	fun3.coordinateSearch(x0, e, xM);
	coordinateEval.push_back(fun3.getNoOfCalls());
	coordinateMin.push_back(xM);

	JakobovicFunction fun4 = JakobovicFunction();
	x0 = { 5.1, 1.1 };
	e = { 0.000001, 0.000001 };
	fun4.resetNoOfCalls();

	xM = fun4.nelderMead(x0, 1, 0.5, 2, 0.5, 0.5, 0.000001);

	nelderAndMeadEval.push_back(fun4.getNoOfCalls());
	nelderAndMeadMin.push_back(xM);

	fun4.resetNoOfCalls();

	Dx = { 0.5, 0.5 };
	xM = fun4.hookeJeeves(x0, Dx, e);

	hookeJeevesEval.push_back(fun4.getNoOfCalls());
	hookeJeevesMin.push_back(xM);

	fun4.resetNoOfCalls();

	fun4.coordinateSearch(x0, e, xM);
	coordinateEval.push_back(fun4.getNoOfCalls());
	coordinateMin.push_back(xM);


	std::cout << "Nelder and Mead fun evaluations: ";
	GoalFunction::printVector(nelderAndMeadEval);

	std::cout << "Hooke Jeeves fun evaluations: ";
	GoalFunction::printVector(hookeJeevesEval);
	
	std::cout << "Coordinate search fun evaluations: ";
	GoalFunction::printVector(coordinateEval);

	std::cout << std::endl;

	std::cout << "Nelder and Mead mins" << std::endl;
	for (int i = 0; i < 4; i++) {
		GoalFunction::printVector(nelderAndMeadMin[i]);
	}
	
	std::cout << std::endl;
	std::cout << "Hooke Jeeves mins" << std::endl;
	for (int i = 0; i < 4; i++) {
		GoalFunction::printVector(hookeJeevesMin[i]);
	}

	std::cout << std::endl;

	std::cout << "Coordinate search mins" << std::endl;
	for (int i = 0; i < 4; i++) {
		GoalFunction::printVector(coordinateMin[i]);
	}
	std::cout << std::endl;
	

}


void zadatak3() {

	JakobovicFunction fun1 = JakobovicFunction();
	std::vector<double> x0 = { 5,  5 };
	std::vector<double> e = { 0.000001, 0.000001 };
	std::vector<double> xM;


	fun1.resetNoOfCalls();

	xM = fun1.nelderMead(x0, 1, 0.5, 2, 0.5, 0.5, 0.000001);

	int nelderAndMeadEval = fun1.getNoOfCalls();
	std::vector<double> nelderMin = xM;

	fun1.resetNoOfCalls();

	std::vector<double> Dx = { 0.5, 0.5 };
	xM = fun1.hookeJeeves(x0, Dx, e);

	int hookeJeevesEval = fun1.getNoOfCalls();
	std::vector<double> hookeJeevesMin = xM;

	std::cout << "No of calls for function (Nelder and Mead, Hooke-Jeeves respectively) :  " 
		<< nelderAndMeadEval << "  " << hookeJeevesEval;
	std::cout << std::endl;

	std::cout << "Calculated minimums: " << std::endl;

	GoalFunction::printVector(nelderMin);
	GoalFunction::printVector(hookeJeevesMin);

}

void zadatak4() {

	RosenbrockFunction fun = RosenbrockFunction();
	std::vector<double> x0 = { 0.5, 0.5 };

	//odredeni koraci za eksperiment
	std::vector<double> steps = { 1, 5, 7, 12, 15, 20 };
	std::vector<double> min;

	std::vector<std::vector<double>> mins;
	std::vector<double> funCalls;

	for (int i = 0; i < steps.size(); i++) {
	
		fun.resetNoOfCalls();

		min = fun.nelderMead(x0, 1, 0.5, 2, steps[i], 0.5, 0.000001);
		
		funCalls.push_back(fun.getNoOfCalls());
		
		mins.push_back(min);

	}

	std::cout << "Function calls for all steps respectively:  " << std::endl;
	GoalFunction::printVector(funCalls);

	std::cout << " Minimums calculated for all steps:  " << std::endl;

	for (int i = 0; i < mins.size(); i++) {

		GoalFunction::printVector(mins[i]);

	}

}


void zadatak5() {


	SchaffersFunction fun = SchaffersFunction();
	int steps = 0;
	std::vector<double> dx = { 0.5, 0.5 };
	std::vector<double> e = { 0.000001, 0.000001 };
	while (true) {
		steps++;
		double l = rand() % 100 - 50;
		double r = rand() % 100 - 50;

		std::vector<double> x0 = { l, r };

		std::vector<double> min = fun.hookeJeeves(x0, dx, e);

		if (fun.function(min) < 0.0001) break;
	}

	std::cout << "Probability = " << 1 / steps;
}