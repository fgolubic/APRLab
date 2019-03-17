#include<iostream>
#include"Matrix.h"


int main(void) {


	/*
		1. PRIMJER	
	
	*/

	Matrix mat1 = Matrix("matrica.txt");

	Matrix mat2 = Matrix(mat1);

	std::cout << "Check if 2 loaded matrices are  same: " << (mat1 == mat2) << std::endl;

	mat2 *= 3;
	mat2 /= 3;

	bool flag = ( mat2 == mat1 );

	std::cout << "Are matrices same afrer multiplying and dividing by 3? " << std::endl;

	if (!flag) {
		std::cout << "No\n\n\n" << std::endl << std:: endl;
		mat1.printMatrix();
		std::cout << std::endl;
		mat2.printMatrix();
	}

	else {
		std::cout << "Yes\n\n\n" << std::endl << std::endl;
	}

	mat1.printMatrix("test.txt");


	//2. Primjer
	std::cout << "Running second example:" << std::endl;
	run("matrica2.txt", "vector2.txt");
	std::cout << "End of second example.\n\n\n\n" << std::endl;


	//3. Primjer
	std::cout << "Running third example:" << std::endl;
	run("matrica3.txt", "vector2.txt");
	std::cout << "End of third example.\n\n\n\n" << std::endl;


	//4. Primjer
	std::cout << "Running fourth example:" << std::endl;
	run("matrica4.txt", "vector4.txt");
	std::cout << "End of fourth example.\n\n\n\n" << std::endl;


	//5. Primjer
	std::cout << "Running fifth example:" << std::endl;
	run("matrica5.txt", "vector5.txt");
	std::cout << "End of fifth example.\n\n\n\n" << std::endl;

	//6. Primjer
	std::cout << "Running sixth example:" << std::endl;
	run("matrica6.txt", "vector6.txt");
	std::cout << "End of sixth example.\n\n\n\n" << std::endl;


	std::cin >> flag;

	return 0;
}



void run(std::string matrixFile, std::string vectorFile) {
	Matrix empty = Matrix();
	Matrix mat = Matrix(matrixFile);

	//hardcoded for 6th example
	if (matrixFile == "matrica6.txt") {
		mat.eps = 0.0000001;
	}


	Matrix vector = Matrix(vectorFile);
	Matrix b = ~vector;
	Matrix vectY, vectX;
	Matrix matA = mat.decompositionLU();
	

	if (matA != empty ) {
		std::cout << "LU decomposition matrix:" << std::endl;

		matA.printMatrix();

		vectY = matA.forwardSupsitution(b);

		std::cout << "Vector Y of LU decomposition: " << std::endl;
		vectY.printMatrix();

		vectX = matA.backwardSupsitution(vectY);

		std::cout << "Vector X of LU decomposition: " << std::endl;
		vectX.printMatrix();
	}


	Matrix matP;

	matA = mat.decompositionLUP(matP);

	if (matA != empty) {
		std::cout << "LUP decomposition matrix:" << std::endl;

		matA.printMatrix();

		std::cout << "LUP permutation matrix:" << std::endl;

		matP.printMatrix();

		vectY = matA.forwardSupsitution(matP*b);

		std::cout << "Vector Y of LUP decomposition: " << std::endl;

		vectY.printMatrix();

		vectX = matA.backwardSupsitution(vectY);

		std::cout << "Vector X of LUP decomposition: " << std::endl;

		vectX.printMatrix();

	}
}