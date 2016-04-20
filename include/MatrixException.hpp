#pragma once
#include <exception>
#include "iostream"
using namespace std;

class MatrixException : public std::exception {
public:
	MatrixException() : std::exception(invalid_argument("Unknown exception")) {}
	MatrixException(const char *_message) : std::exception(invalid_argument(_message)) {}
};
class FileException : public MatrixException {
public:
	FileException() : MatrixException("File cannot be opened") {};
};
class SizesException : public MatrixException {
public:
	SizesException() : MatrixException("Wrong sizes of matrix") {};
};
class StreamException : public MatrixException {
public:
	StreamException() : MatrixException("Fill error: bad stream") {};
};
class IndexException : public MatrixException {
public:
	IndexException() : MatrixException("Index >= number of lines") {};
};
class AddException : public MatrixException {
public:
	AddException() : MatrixException("left_matrix.columns != right_matrix.columns\
 || left_matrix.lines != right_matix.lines") {};
};
class MultiplyException : public MatrixException {
public:
	MultiplyException() : MatrixException("left_matrix.columns != right_matrix.lines") {};
};
