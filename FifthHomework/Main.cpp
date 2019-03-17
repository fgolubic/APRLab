#include<iostream>
#include"Assigment.h"
#include"RungeKutta.h"
#include"Trapeziodal.h"


int main(int argc, char** argv) {
	char a;

	zadatak4();

	std::cin >> a;

	return 0;
}

void zadatak1() {

	Matrix A("prvi.txt");

	Matrix B = !A;

	B.printMatrix();
}

void zadatak2() {

	Matrix A("drugi.txt");

	Matrix B = !A;

	B.printMatrix();
}

void zadatak3() {

	Matrix A("treci.txt");

	Matrix B = Matrix(2, (int)1);

	Matrix x0 = Matrix(2, (int)1);
	x0[0][0] = 1.0;
	x0[1][0] = 2.0;

	auto res = RungeKuttaMethod(x0, A, B, 0.1, 10);

	if (toFile(res, "result.txt")) std::cout << "Success!";

	else std::cout << "Failed!";

}

void zadatak4() {

	Matrix A("cetvrti.txt");

	Matrix B = Matrix(2, (int)1);

	Matrix x0 = Matrix(2, (int)1);
	x0[0][0] = 1.0;
	x0[1][0] = -2.0;

	auto res = RungeKuttaMethod(x0, A, B, 0.5, 10);

	if (toFile(res, "result.txt")) std::cout << "Success!"<<std::endl;

	else std::cout << "Failed!"<<std::endl;


	auto resTrap = TrapeziodalApproximation(x0, A, B, 0.1, 10);

	if (toFile(resTrap, "resultTrap.txt")) std::cout << "Success!";

	else std::cout << "Failed!";


}