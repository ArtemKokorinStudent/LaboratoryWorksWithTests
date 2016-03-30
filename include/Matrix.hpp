#ifndef Matrix_hpp
#define Matrix_hpp

#include <iostream>

class Matrix {
public:
	Matrix() : lines(0), columns(0), elements(nullptr) {}
	Matrix(int _lines, int _columns);
	Matrix(const Matrix& source_matrix);
	Matrix& operator= (const Matrix& source_matrix);
	void InitFromRandom();
	void InitFromFile(char *filename);
	void Output() const;
	int* operator[](int index) const;
	const Matrix operator+(const Matrix& right_matrix); 
	const Matrix operator*(const Matrix& right_matrix); 
	int GetNumberOfLines() const;
	int GetNumberOfColumns() const;
	~Matrix();
private:
	int lines, columns, **elements;
};

Matrix::Matrix(int _lines, int _columns)  :
	lines(_lines), columns(_columns), elements(new int*[_lines]) {
	for (int i = 0; i < lines; i++) {
		elements[i] = new int[columns];
		for (int j = 0; j < columns; j++){
			elements[i][j] = 0;
		}
	}
}
Matrix::Matrix(const Matrix& source_matrix)
	: lines(source_matrix.lines), columns(source_matrix.columns) {
	elements = new int*[lines];
	for (int i = 0; i < lines; i++) {
		elements[i] = new int[columns];
		for (int j  = 0; j < columns; j++) {
			elements[i][j] = source_matrix[i][j];
		}
	}
}
Matrix& Matrix::operator= (const Matrix& source_matrix) {
	if (lines != source_matrix.lines || columns != source_matrix.columns) {
		this -> ~Matrix();
		lines = source_matrix.lines;
		columns = source_matrix.columns;
		elements = new int*[lines];
		for (int i = 0; i < lines; i++) {
			elements[i] = new int[columns];
			for (int j = 0; j < columns; j++) {
				elements[i][j] = source_matrix[i][j];
			}
		}
	} else{
		for (int i = 0; i < lines; i++){
			for (int j = 0; j < columns; j++){
				elements[i][j] = source_matrix[i][j];
			}
		}
	}
	return *this;
}
void Matrix::InitFromRandom() {
	for (int i = 0; i < lines; i++)
		for (int j = 0; j < columns; j++)
			elements[i][j] = rand() % 90 + 10;
}
void Matrix::InitFromFile(char *filename) {
	std::fstream file(filename);
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			file >> elements[i][j];
		}
	}
}
void Matrix::Output() const {
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++)
			std::cout << elements[i][j] << " ";
		std::cout << "\n";
	}
}
int*  Matrix::operator[](int index) const {
	return elements[index];
}
Matrix Matrix::operator+(const Matrix& right_matrix) const {
	if (columns != right_matrix.GetNumberOfColumns()
		|| lines != right_matrix.GetNumberOfLines())
		return *(new Matrix());
	Matrix result(lines, columns);
	for (int i = 0; i < lines; i++)
		for (int j = 0; j < columns; j++)
			result[i][j] = elements[i][j] + right_matrix[i][j];
	return result;
}
Matrix Matrix::operator*(const Matrix& right_matrix) const {
	if (columns != right_matrix.lines) return *(new Matrix());
	Matrix result(lines, right_matrix.columns);
	for (int i = 0; i < lines; i++)
		for (int j = 0; j < right_matrix.columns; j++) {
			result[i][j] = 0;
			for (int k = 0; k < right_matrix.lines; k++)
				result[i][j] += elements[i][k] * right_matrix[k][j];
		}
	return result;
}
int Matrix::GetNumberOfLines() const {
	return lines;
}
int Matrix::GetNumberOfColumns() const {
	return columns;
}
Matrix::~Matrix() {
	for (int i = 0; i < lines; i++)
		delete[] elements[i];
	delete[] elements;
}

#endif
