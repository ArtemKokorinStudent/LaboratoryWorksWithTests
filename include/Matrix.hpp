#ifndef Matrix_hpp
#define Matrix_hpp
//https://msdn.microsoft.com/ru-ru/library/f1b2td24.aspx
#include <iostream>
#include <fstream>
#include "MatrixException.hpp"

template <class MatrixT> class Matrix;
template <class MatrixT> std::istream& operator>> (std::istream& stream, Matrix<MatrixT>& matrix) throw (StreamException);
template <class MatrixT> std::ostream& operator<< (std::ostream& stream, const Matrix<MatrixT>& matrix);

template <class MatrixT = int>
class Matrix {
public:
	Matrix() : lines(0), columns(0), elements(nullptr) {}
	Matrix(size_t _lines, unsigned int _columns);
	Matrix(const Matrix<MatrixT>& source_matrix);
	Matrix& operator= (const Matrix& source_matrix);
	void InitFromRandom();
	void InitFromFile(const char *filename) throw (FileException);
	MatrixT* operator[](unsigned int index) const throw (IndexException);
	Matrix<MatrixT> operator+(const Matrix<MatrixT>& right_matrix) const throw (AddException);
	Matrix<MatrixT> operator*(const Matrix<MatrixT>& right_matrix) const throw (MultiplyException);
	bool operator==(const Matrix<MatrixT>& right_matrix) const;
	bool operator!=(const Matrix<MatrixT>& right_matrix) const;
	unsigned int GetNumberOfLines() const;
	unsigned int GetNumberOfColumns() const;
	~Matrix();
	//template <class MatrixT>
	friend std::istream& operator>> <>(std::istream& stream, Matrix<MatrixT>& matrix) throw (StreamException);
	//template <class MatrixT>
	friend std::ostream& operator<< <>(std::ostream& stream, const Matrix<MatrixT>& matrix);
private:
	MatrixT **elements;
	unsigned int lines, columns;
};

template <class MatrixT>
std::istream& operator>> (std::istream& stream, Matrix<MatrixT>& matrix) throw (StreamException){
	for (unsigned int i = 0; i < matrix.lines; i++) {
		for (unsigned int j = 0; j < matrix.columns; j++) {
			if (!(stream >> matrix[i][j])) {
				throw StreamException();
			}
		}
	}
	return stream;
}
template <class MatrixT>
std::ostream& operator<< (std::ostream& stream, const Matrix<MatrixT>& matrix) {
	for (unsigned int i = 0; i < matrix.lines; i++) {
		for (unsigned int j = 0; j < matrix.columns; j++) {
			stream << matrix[i][j] << " ";
		}
		stream << '\n';
	}
	return stream;
}
template <typename MatrixT>
Matrix<MatrixT>::Matrix(size_t _lines, unsigned int _columns) :
	lines(_lines), columns(_columns), elements(new MatrixT*[_lines]) {
	for (unsigned int i = 0; i < lines; i++) {
		elements[i] = new MatrixT[columns];
		for (unsigned int j = 0; j < columns; j++) {
			elements[i][j] = 0;
		}
	}
}

template <typename MatrixT>
Matrix<MatrixT>::Matrix(const Matrix<MatrixT>& source_matrix)
	: lines(source_matrix.lines), columns(source_matrix.columns) {
	elements = new MatrixT*[lines];
	for (unsigned int i = 0; i < lines; i++) {
		elements[i] = new MatrixT[columns];
		for (unsigned int j = 0; j < columns; j++) {
			elements[i][j] = source_matrix[i][j];
		}
	}
}

template <typename MatrixT>
Matrix<MatrixT>& Matrix<MatrixT>::operator= (const Matrix<MatrixT>& source_matrix) {
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
	}
	else {
		for (int i = 0; i < lines; i++) {
			for (int j = 0; j < columns; j++) {
				elements[i][j] = source_matrix[i][j];
			}
		}
	}
	return *this;
}

template <typename MatrixT>
void Matrix<MatrixT>::InitFromRandom() {
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			elements[i][j] = rand() % 90 + 10;
		}
	}
}

template <typename MatrixT>
void Matrix<MatrixT>::InitFromFile(const char *filename) throw (FileException){
	std::fstream file(filename);
	if (!file) throw FileException();
	file >> *this;
}

template <typename MatrixT>
MatrixT* Matrix<MatrixT>::operator[](unsigned int index) const throw (IndexException){
	if (index >= lines) throw IndexException();
	return elements[index];
}

template <typename MatrixT>
Matrix<MatrixT> Matrix<MatrixT>::operator+(const Matrix<MatrixT>& right_matrix) const throw (AddException){
	if (columns != right_matrix.GetNumberOfColumns()
		|| lines != right_matrix.GetNumberOfLines())
		throw AddException();
	Matrix<MatrixT> result(lines, columns);
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			result[i][j] = elements[i][j] + right_matrix[i][j];
		}
	}
	return result;
}

template <typename MatrixT>
Matrix<MatrixT> Matrix<MatrixT>::operator*(const Matrix& right_matrix) const throw (MultiplyException) {
	if (columns != right_matrix.lines) throw MultiplyException();
	Matrix<MatrixT> result(lines, right_matrix.columns);
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < right_matrix.columns; j++) {
			result[i][j] = 0;
			for (int k = 0; k < right_matrix.lines; k++)
				result[i][j] += elements[i][k] * right_matrix[k][j];
		}
	}
	return result;
}

template<typename MatrixT>
bool Matrix<MatrixT>::operator==(const Matrix<MatrixT>& right_matrix) const
{
	if (lines != right_matrix.lines || columns != right_matrix.columns) {
		return false;
	}
	else {
		for (unsigned i = 0; i < lines; i++) {
			for (unsigned j = 0; j < columns; j++) {
				if (operator[](i)[j] != right_matrix[i][j]) {
					return false;
				}
			}
		}
		return true;
	}
}

template<typename MatrixT>
bool Matrix<MatrixT>::operator!=(const Matrix<MatrixT>& right_matrix) const
{
	return !(operator==(right_matrix));
}

template <typename MatrixT>
unsigned int Matrix<MatrixT>::GetNumberOfLines() const {
	return lines;
}

template <typename MatrixT>
unsigned int Matrix<MatrixT>::GetNumberOfColumns() const {
	return columns;
}

template <typename MatrixT>
Matrix<MatrixT>::~Matrix() {
	for (unsigned int i = 0; i < lines; i++)
		delete[] elements[i];
	delete[] elements;
}

#endif


