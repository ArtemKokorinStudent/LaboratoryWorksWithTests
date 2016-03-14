#ifndef Matrix_hpp
#define Matrix_hpp

#include <iostream>

class Matrix
{
public:
    Matrix(const Matrix &matrix);
    Matrix(unsigned int rows, unsigned int columns);
    virtual ~Matrix();
    unsigned int rows() const;
    unsigned int columns() const;
    bool fill(const std::string filePath);
    void show() const;
    const int *operator[](unsigned int index) const;
    
    Matrix operator*(const Matrix &matrix) const;
    Matrix operator+(const Matrix &matrix) const;
    bool operator==(const Matrix &matrix) const;
    Matrix & operator=(const Matrix &matrix);
private:
    unsigned int m_rows, m_columns;
    int **m_elements;
    
    Matrix(unsigned int rows, unsigned int columns, int **elements);
    void swap(Matrix &matrix);
    void fill(int **elements);
};


#endif