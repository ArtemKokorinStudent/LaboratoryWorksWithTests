#include <string>
#include <iostream>
#include <fstream>

#include "Matrix.hpp"

Matrix::Matrix(const Matrix &matrix) : m_rows(matrix.m_rows), m_columns(matrix.m_columns)
{
    fill(matrix.m_elements);
}

Matrix::Matrix(unsigned int rows, unsigned int columns) : m_rows(rows), m_columns(columns)
{
    fill(nullptr);
}

Matrix::Matrix(unsigned int rows, unsigned int columns, int **elements) : m_rows(rows), m_columns(columns)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    fill(elements);
}

void Matrix::fill(int **elements)
{
    m_elements = new int *[m_columns];
    for (unsigned int i = 0; i < m_columns; ++i) {
        m_elements[i] = new int[m_rows];
        for (unsigned int j = 0; j < m_rows; ++j) {
            m_elements[i][j] = elements ? elements[i][j] : 0;
        }
    }
}

Matrix & Matrix::operator=(const Matrix &matrix)
{
    if ( this != &matrix ) {
        Matrix(matrix).swap(*this);
    }

    return *this;
}

void Matrix::swap(Matrix &matrix)
{
    std::swap(m_rows, matrix.m_rows);
    std::swap(m_columns, matrix.m_columns);
    std::swap(m_elements, matrix.m_elements);
}

Matrix::~Matrix()
{
    for (unsigned int i = 0; i < m_rows; ++i) {
        delete [] m_elements[i];
    }

    delete [] m_elements;
}

unsigned int Matrix::rows() const
{
    return m_rows;
}

unsigned int Matrix::columns() const
{
    return m_columns;
}

bool Matrix::fill(const std::string filePath)
{
    std::ifstream input;
    input.open(filePath);

    bool isSucess = true;
    if ( input.is_open() ) {
        for (unsigned int i = 0; i < m_rows; ++i) {
            for (unsigned int j = 0; j < m_columns; ++j) {
                if ( !(input >> m_elements[i][j]) ) {
                    throw "exception in fill matrix";
                }
            }
        }
    }
    else {
        isSucess = false;
    }

    input.close();

    return isSucess;
}

const int *Matrix::operator[](unsigned int index) const
{
    if ( index >= m_rows ) {
        throw std::invalid_argument("index goes abroad");
    }

    return m_elements[index];
}

Matrix Matrix::operator *(const Matrix &matrix) const
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    if ( m_columns != matrix.m_rows ) {
        throw std::invalid_argument("matrix sizes do not match");
    }

    unsigned int n = m_rows;
    unsigned int m = matrix.m_columns;
    unsigned int s = m_columns;

    int **elements = new int *[n];
    for (unsigned int i = 0; i < n; ++i) {
        elements[i] = new int[m];
        for (unsigned int j = 0; j < m; ++j) {
            int value = 0;
            for (unsigned int k = 0; k < s; ++k) {
                value += m_elements[i][k] * matrix.m_elements[k][j];
            }
            elements[i][j] = value;
        }
    }

    return Matrix(n, m, elements);
}


Matrix Matrix::operator +(const Matrix &matrix) const
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    if ( m_rows != matrix.m_rows || m_columns != matrix.m_columns ) {
        throw std::invalid_argument("matrix sizes do not match");
    }

    unsigned int n = m_rows;
    unsigned int m = m_columns;

    int **data = new int *[n];
    for (unsigned int i = 0; i < n; ++i) {
        data[i] = new int[m];
        for (unsigned int j = 0; j < m; ++j) {
            data[i][j] = m_elements[i][j] + m_elements[i][j];
        }
    }

    return Matrix(n, m, data);
}

bool Matrix::operator==(const Matrix &matrix) const
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    if ( m_rows != matrix.m_rows || m_columns != matrix.m_columns ) {
        return false;
    }

    for (unsigned int i = 0; i < m_rows; ++i) {
        for (unsigned int j = 0; j < m_columns; ++j) {
            if ( m_elements[i][j] != matrix.m_elements[i][j] ) {
                return false;
            }
        }
    }

    return true;
}

void Matrix::show() const
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    std::cout << m_rows << " * " << m_columns << std::endl;
    for (unsigned int i = 0; i < m_rows; ++i) {
        for (unsigned int j = 0; j < m_columns; ++j) {
            std::cout << m_elements[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
