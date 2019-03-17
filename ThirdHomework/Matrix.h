/*
 * Matrix.h
 *
 *  Created on: Oct 2, 2018
 *      Author: fgolubic
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include<iomanip>
#include<conio.h>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

#define EPSILON 0.000999

class Matrix {
private:
	unsigned int noOfRows; //number of rows of matrix object
	unsigned int noOfColumns; //number of columns of matrix object
	std::vector<std::vector<double>>* matrix; //pointer to the 2d vector of doubles representing matrix container
public:
	double eps = 0.0001; //parameter needed for tuning LU(P) composition
	/**
		Creates new empty matrix size 0x0
	*/
	Matrix();
	/**
		Creates matrix of size n x m with all elements zeros.
	*/
	Matrix(int n, int m);
	/**
		Creates indentity matrix of size n. If value set to other then one then diagonal elements will have that given value.
	*/
	Matrix(int n, double value = 1.0);
	/**
		Creates new matrix from a file given with a filePath
		@param [in] filePath - path to matrix file
	*/
	Matrix(std::string filePath);

	/**
		Copy-constructor
		@param [in] matrix - reference to matrix object
	*/
	Matrix(const Matrix & matrix);

	/**
		Virtual destructor. Releases memory of matrix.
	*/
	virtual ~Matrix();

	/**
		Getter for number of rows.
		@param [out] number of matrix rows
	*/
	unsigned int getNoOfRows() const;

	/**
		Getter for number of columns.
		@param [out] number of matrix columns
	*/
	unsigned int getNoOfColumns() const;

	Matrix getColumn(int index);

	/**
		Setter for number of rows. 
		@param [in] new value of number of rows.
	*/
	void setNoOfRows(unsigned int noOfRows);

	/**
		Setter for number of columns.
		@param [in] new value of number of columns.
	*/
	void setNoOfColumns(unsigned int noOfColumns);

	/**
		Getter for 2d vector array respresentation of matrix.
		@params [out] 2d vector representation of matrix.
	*/
	std::vector<std::vector<double>>& getMatrix() const;

	/**
		Prints formatted matrix to a stdin.
	*/
	void printMatrix();

	/**
		Prints matrix to a file. File created if it doesn't exist.
		@param [in] fileName - path to the file
	*/
	void printMatrix(std::string fileName);


	//overloaded operators as members of a class
	Matrix operator=(const Matrix& secondMatrix);
	std::vector<double> operator[](int index) const;
	std::vector<double>& operator[](int index);
	Matrix operator+=(const Matrix& secondMatrix);
	Matrix operator-=(const Matrix& secondMatrix);
	Matrix operator*=(double factor);
	Matrix operator/=(double factor);
	Matrix operator~();
	bool operator==(const Matrix& secondMatrix);
	bool operator!=(const Matrix& secondMatrix);
	Matrix operator!();

	/**
		Method for forward supstitution algorithm. Ly = Pb.

		@param [in] freeVector - vector Matrix of Pb
		@param [out] y - vector Matrix of y
	*/
	Matrix forwardSupsitution(Matrix freeVector);

	/**
		Method for backward supstitution algorithm. Ux = Py.

		@param [in] freeVector - vector Matrix of Py
		@param [out] y - vector Matrix of x
	*/
	Matrix backwardSupsitution(Matrix freeVector);

	/**
		Matrix LU decomposition algorithm. Makes epsilon check.
		@param [out] LU Matrix object
	*/
	Matrix decompositionLU();

	/**
		Matrix LUP decomposition algorithm with pivoting using Matrix P.  Makes epsilon check.
		Populates empty pivot Matrix.
		@param [in,out] P matrix 
		@param [out] LUP Matrix object
	*/
	Matrix decompositionLUP(Matrix& matrixP);

	/**
		Switch two rows of a matrix.
		@param[in] indexes of two rows that needs to be switched
	*/
	Matrix switchRows(unsigned int first, unsigned int second);

	/**
		Switch two columns of a matrix.
		@param[in] indexes of two columns that needs to be switched.
	*/
	Matrix switchColumns(unsigned int first, unsigned int second);

	/**
		Permute free vector b based on permutational vector Matrix P.
		@param [in] permutational vector P
		@param [out] permuted free vector b
	*/
	Matrix permuteMatrix(const Matrix& permutationVector);

	

};


//overloaded operators as non class members
Matrix operator+(const Matrix& matrixA, const Matrix& matrixB);
Matrix operator-(const Matrix& matrixA, const Matrix& matrixB);
Matrix operator*(const Matrix& matrixA, const Matrix& matrixB);
Matrix operator*(double factor, const Matrix& matrix);
Matrix operator*(const Matrix& matrix, double factor);
Matrix operator/(const Matrix& matrix, double factor);

/**
	Method for running and printing results of LU and LUP decomposition on given Matrix and free vector (A, b). 
	@param [in] paths to Matrix and vector file; needed to consturct Matrix objects
*/
void run(std::string matrixFile, std::string vectorFile);


#endif /* MATRIX_H_ */
