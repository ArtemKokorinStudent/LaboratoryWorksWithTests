#pragma once
#include <exception>
#include "iostream"
using namespace std;

class BinarySearchTreeException : public std::exception {
public:
	BinarySearchTreeException() : std::exception(invalid_argument("Unknown exception")) {}
	BinarySearchTreeException(const char *_message) : std::exception(invalid_argument(_message)) {}
};
class FileException : public BinarySearchTreeException {
public:
	FileException() : BinarySearchTreeException("File cannot be opened") {};
};
class FileEndException : public BinarySearchTreeException {
public:
	FileEndException() : BinarySearchTreeException("Unexpected end of file") {};
};
class StreamException : public BinarySearchTreeException {
public:
	StreamException() : BinarySearchTreeException("Fill error: bad stream") {};
};
