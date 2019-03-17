/*
 * Matrix.cpp
 *
 *  Created on: Oct 2, 2018
 *      Author: fgolubic
 */

#include "Matrix.h"

Matrix::Matrix() {

	this->noOfRows = 0;
	this->noOfColumns = 0;

	this->matrix = new std::vector<std::vector<double>>();


}

Matrix::Matrix(std::string filePath)
{
	std::ifstream file(filePath);

	if(!file.is_open())
	{
		std::cerr << "Error opening file" << std::endl;
		return;
	}

	std::cout<<"Reading matrix from a file " << filePath << "." << std::endl;

	std::string line;

	noOfRows = 0;
	noOfColumns = 0;
	matrix = new std::vector<std::vector<double>>();

	int rowCounter = 0;

	while(std::getline(file, line)){

		std::cout<<"Reading row " << ( rowCounter + 1 ) << "." <<std::endl;

		std::istringstream lineStream(line);
		std::string token;
		std::vector<double> row = std::vector<double>();


		while( lineStream >> token ){

			std::cout<<"Splitting elements from row "<< ( rowCounter + 1 ) << "." << std::endl;

			double element = std::stod(token);

			row.push_back(element);

		}

		if(noOfColumns == 0){

			noOfColumns = row.size();

			std::cout<<"No. of columns set to " << noOfColumns << "." << std::endl;

		}

		else if( noOfColumns != row.size() ){

			std::cerr << "Matrix wrongly defined in file!" << std::endl;
			return;

		}

		matrix->push_back(row);

	}

	noOfRows = matrix->size();

	std::cout<<"No. of rows set to "<< noOfRows << "." << std::endl;

}

Matrix::Matrix(const Matrix & matrixIn) {

	this->noOfRows = matrixIn.noOfRows;
	this->noOfColumns = matrixIn.noOfColumns;

	this->matrix = new std::vector<std::vector<double>>(matrixIn.matrix->begin(), matrixIn.matrix->end());

}

Matrix::~Matrix() {
	
	this->noOfRows = 0;
	this->noOfColumns = 0;
	delete matrix;
}

unsigned int Matrix::getNoOfRows() const{

	return this->noOfRows;

}

unsigned int Matrix::getNoOfColumns() const{

	return this->noOfColumns;

}

void Matrix::setNoOfColumns(unsigned int noOfColumns){

	this->noOfColumns = noOfColumns;

}

void Matrix::setNoOfRows(unsigned int noOfRows){

	this->noOfRows = noOfRows;

}

std::vector<std::vector<double>>& Matrix::getMatrix() const{

	return *(this->matrix);

}

void Matrix::printMatrix() {

	for (unsigned int i = 0; i < this->noOfRows; i++) {

		for (unsigned int j = 0; j< this->noOfColumns; j++){
			
			std::cout << std::setw(8) << (*(this->matrix))[i][j] << " ";
		
		}

		std::cout << std::endl;

	}

}

void Matrix::printMatrix(std::string fileName) {

	std::ofstream file;
	file.open(fileName);

	if (!file.is_open())
	{
		std::cerr << "Error opening file" << std::endl;
		return;
	}

	std::cout << "File opened: " << fileName << std::endl;
	
	for (unsigned int i = 0; i < this->getNoOfRows(); i++) {

		for (unsigned int j = 0; j < this->getNoOfColumns(); j++) {
			file << (*this)[i][j];
			file << "  ";
		}
		file << "\n";
	}

	std::cout << "Closing file: " << fileName << std::endl;
	file.close();
}

Matrix Matrix::operator=(const Matrix& secondMatrix){

	this->matrix->erase(this->matrix->begin(), this->matrix->end());

	for(unsigned int i=0; i < secondMatrix.noOfRows; i++ ){

		std::vector<double> secondMatrixRow = (*(secondMatrix.matrix))[i];

		(this->matrix)->push_back(std::vector<double>(secondMatrixRow.begin(), secondMatrixRow.end()));

	}

	this->noOfColumns = secondMatrix.noOfColumns;
	this->noOfRows = secondMatrix.noOfRows;

	return *this;
}

std::vector<double> Matrix::operator[](int index) const{

	return (*(this->matrix))[index];
}

std::vector<double>& Matrix::operator[](int index){

	return (*(this->matrix))[index];

}



Matrix Matrix::operator+=(const Matrix& secondMatrix){

	if ((this->noOfColumns != secondMatrix.noOfColumns) || (this->noOfRows != secondMatrix.noOfRows)) {

		std::cerr << "Matrices not compatibile for this operation (+)!" << std::endl;

		exit(2);
	}

	for (unsigned int i = 0; i < this->noOfRows; i++ ) {

		for (unsigned int j = 0; j < this->noOfColumns; j++) {

			(*(this->matrix))[i][j] += (*(secondMatrix.matrix))[i][j];

		}
	}

	return *this;

}


Matrix Matrix::operator-=(const Matrix& secondMatrix) {


	if ((this->noOfColumns != secondMatrix.noOfColumns) || (this->noOfRows != secondMatrix.noOfRows)) {

		std::cerr << "Matrices not compatibile for this operation (-) !" << std::endl;

		exit(2);
	}

	for (unsigned int i = 0; i < this->noOfRows; i++) {

		for (unsigned int j = 0; j < this->noOfColumns; j++) {

			(*(this->matrix))[i][j] -= (*(secondMatrix.matrix))[i][j];

		}
	}

	return *this;


}

Matrix operator-(const Matrix & matrixA, const Matrix & matrixB)
{
	Matrix result = Matrix(matrixA);

	return result-=matrixB;
}

Matrix Matrix::operator*=(double factor)
{
	for(int i = 0; i < this->noOfRows; i++){

		for (int j = 0; j < this->noOfColumns; j++) {

			(*(this->matrix))[i][j] *= factor;

		}

	}

	return *this;
}

Matrix operator+(const Matrix & matrixA, const Matrix & matrixB)
{
	Matrix result = Matrix(matrixA);

	return result += matrixB;
}


Matrix operator*(double factor, const Matrix& matrix) {

	Matrix result = Matrix(matrix);

	return result *= factor;

}

Matrix operator*(const Matrix& matrix, double factor) {

	Matrix result = Matrix(matrix);

	return result *= factor;

}

Matrix operator*(const Matrix& matrixA, const Matrix& matrixB) {

	if (matrixA.getNoOfColumns() != matrixB.getNoOfRows()) {

		std::cerr << "Matrices not compatibile for this operation (*)!" << std::endl;

		exit(3);
	}

	Matrix result = Matrix();

	for (unsigned int i = 0; i < matrixA.getNoOfRows(); i++) {

		std::vector<double> row = std::vector<double>();

		for (unsigned int k = 0; k < matrixB.getNoOfColumns(); k++) {
			

			double element = 0;

			for (unsigned int j = 0; j < matrixB.getNoOfRows(); j++) {

				element += matrixA[i][j] * matrixB[j][k];


			}
			
			row.push_back(element);


		}

		result.getMatrix().push_back(row);

	}

	result.setNoOfRows(matrixA.getNoOfRows());

	result.setNoOfColumns(matrixB.getNoOfColumns());

	return result;
}

Matrix Matrix::operator/=(double factor) {

	double multFactor = 1 / factor;

	return (*this) *= multFactor;


}


Matrix operator/(const Matrix& matrix, double factor) {

	Matrix tempMatrix = Matrix(matrix);

	return tempMatrix/= factor;
}

Matrix Matrix::operator~() {

	Matrix transponse = Matrix();

	for (unsigned int j = 0; j < this->noOfColumns; j++) {

		std::vector<double> newRow = std::vector<double>();

		for (unsigned int i = 0; i < this->noOfRows; i++) {

			newRow.push_back((*this)[i][j]);

		}


		transponse.getMatrix().push_back(newRow);

	}

	transponse.setNoOfColumns(this->noOfRows);

	transponse.setNoOfRows(this->noOfColumns);

	return transponse;

}

bool Matrix::operator==(const Matrix& secondMatrix) {

	if ((this->noOfColumns != secondMatrix.getNoOfColumns()) || (this->noOfRows != secondMatrix.getNoOfRows())) {

		return false;
	}

	for (unsigned int i = 0; i < this->noOfRows; i++) {

		for (unsigned int j = 0; j < this->noOfColumns; j++) {

			if (std::abs((*this)[i][j] - secondMatrix[i][j]) > EPSILON) {

				return false;

			}

		}

	}

	return true;

}

bool Matrix::operator!=(const Matrix& secondMatrix) {

	return !((*this) == secondMatrix);
}

Matrix Matrix::backwardSupsitution(Matrix freeVector) {

	Matrix vectorX = Matrix(freeVector);

	for (int i = this->noOfRows - 1; i >= 0; i--)
	{
		
		vectorX[i][0] /= (*this)[i][i];

		for (int j = 0; j < i; j++)
		{
			vectorX[j][0] -= (*this)[j][i] * vectorX[i][0];
		}
	}

	return vectorX;
}


Matrix Matrix::forwardSupsitution(Matrix freeVector) {

	Matrix vectorY = Matrix(freeVector);

	for (int i = 0; i < this->noOfRows - 1; i++)
	{
		for (int j = i + 1; j < this->noOfRows; j++)
		{
			vectorY[j][0] -= (*this)[j] [i] * vectorY[i] [0];
		}
	}
	return vectorY;

}

Matrix Matrix::decompositionLU() {


	if (this->noOfColumns != this->noOfRows) {

		std::cerr << "Not possible to do decomposition of non quadratic matrix!" << std::endl;

		exit(4);
	}


	Matrix workingMatrix = Matrix(*this);

	for (int i = 0; i < this->noOfRows - 1; i++)
	{
		for (int j = i + 1; j < this->noOfColumns; j++)
		{
			if (std::abs(workingMatrix[i][i]) < this->eps) {

				std::cerr << " LU decomposition stopped - pivot lower then epsilon!" << std::endl;

				return Matrix();

			}
			workingMatrix[j][i] /= workingMatrix[i][ i];

			for (int k = i + 1; k < this->noOfRows; k++)
			{
				workingMatrix[j][k] -= workingMatrix[j][i] * workingMatrix[i][ k];
			}
		}
	}

	return workingMatrix;
}

Matrix Matrix::switchRows(unsigned int first, unsigned int second) {

	Matrix workingMatrix = Matrix(*this);

	std::vector<double> temp = workingMatrix[first];

	workingMatrix[first] = workingMatrix[second];

	workingMatrix[second] = temp;

	return workingMatrix;
}

Matrix Matrix::switchColumns(unsigned int first, unsigned int second) {

	Matrix workingMatrix = Matrix(*this);

	for (unsigned int i = 0; i < workingMatrix.getNoOfRows(); i++) {

		double temp = workingMatrix[i][first];

		workingMatrix[i][first] = workingMatrix[i][second];

		workingMatrix[i][second] = temp;

	}


	return workingMatrix;

}


Matrix Matrix::decompositionLUP(Matrix& matrixP) {


	if (this->noOfColumns != this->noOfRows) {

		std::cerr << "Not possible to do decomposition of non quadratic matrix!" << std::endl;

		exit(4);
	}

	matrixP = Matrix();
	matrixP.setNoOfRows(this->noOfRows);
	matrixP.setNoOfColumns(this->noOfColumns);

	Matrix workingMatrix = Matrix(*this);

	for (int i = 0; i < matrixP.getNoOfRows(); i++)
	{
		std::vector<double> temp;

		for (int j = 0; j < matrixP.getNoOfColumns(); j++) {
			
			if (i == j) {

				temp.push_back(1.0);
			}
			else {
				temp.push_back(0.0);
			}

		}
		matrixP.getMatrix().push_back(temp);
	}

	for (int i = 0; i < this->noOfRows - 1; i++)
	{
		int pivot = i;
		for (int j = i + 1; j < this->noOfRows; j++)
		{
			if (std::abs(workingMatrix[j][i]) > std::abs(workingMatrix[pivot][i])) {

				pivot = j;

			}
			
		}
 		
		if (std::abs(workingMatrix[pivot][i]) < this->eps) {

			std::cerr << " LUP decomposition stopped - pivot lower then epsilon!" << std::endl;

			return Matrix();

		}

		workingMatrix = workingMatrix.switchRows(i, pivot);

		matrixP = matrixP.switchColumns(i, pivot);

		for (int j = i + 1; j < this->noOfRows; j++)
		{
			workingMatrix[j][i] /= workingMatrix[i][i];

			for (int k = i + 1; k < this->noOfRows; k++)
			{
				workingMatrix[j][k] -= workingMatrix[j][i] * workingMatrix[i][k];
			}
		}
	}

	return workingMatrix;
}

Matrix Matrix::permuteMatrix(const Matrix& permutationVector) {

	Matrix workingVector = Matrix(*this);


	for (unsigned int i = 0; i < workingVector.getNoOfRows(); i++) {

		workingVector[i][0] = (*this)[permutationVector[0][i]][0];

	}

	return workingVector;

}
