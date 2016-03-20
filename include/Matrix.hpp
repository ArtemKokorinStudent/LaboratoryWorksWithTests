#ifndef Matrix_hpp
#define Matrix_hpp

#include <iostream>

template <typename T>
class Matrix;

template <class T>
std::ostream & operator<<(std::ostream & output, const Matrix<T> & matrix);

template <class T>
std::istream & operator>>(std::istream & output, Matrix<T> & matrix);

template <typename T>
class Matrix
{
public:
    Matrix(const Matrix & matrix);
    Matrix(unsigned int rows, unsigned int columns);
    virtual ~Matrix();
    unsigned int rows() const;
    unsigned int columns() const;
    const int * operator[](unsigned int index) const;
    Matrix operator*(const Matrix &matrix) const;
    Matrix operator+(const Matrix &matrix) const;
    bool operator==(const Matrix &matrix) const;
    Matrix & operator=(const Matrix &matrix);

    friend std::istream & operator>> <>(std::istream & input, Matrix<T> & matrix);
    friend std::ostream & operator<< <>(std::ostream & output, const Matrix<T> & matrix);
private:
    unsigned int m_rows, m_columns;
    T **m_elements;

    Matrix(unsigned int rows, unsigned int columns, T **elements);
    void swap(Matrix & matrix);
    void fill(T **elements);
};

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &matrix) : m_rows(matrix.m_rows), m_columns(matrix.m_columns)
{
    fill(matrix.m_elements);
}

template <typename T>
Matrix<T>::Matrix(unsigned int rows, unsigned int columns) : m_rows(rows), m_columns(columns)
{
    fill(nullptr);
}

template <typename T>
Matrix<T>::Matrix(unsigned int rows, unsigned int columns, T **elements) : m_rows(rows), m_columns(columns)
{
    fill(elements);
}

template <typename T>
void Matrix<T>::fill(T **elements)
{
    m_elements = new T *[m_columns];
    for (unsigned int i = 0; i < m_columns; ++i) {
        m_elements[i] = new T[m_rows];
        for (unsigned int j = 0; j < m_rows; ++j) {
            m_elements[i][j] = elements ? elements[i][j] : 0;
        }
    }
}

template <typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix & matrix)
{
    if ( this != &matrix ) {
        Matrix(matrix).swap(*this);
    }

    return *this;
}

template <typename T>
void Matrix<T>::swap(Matrix & matrix)
{
    std::swap(m_rows, matrix.m_rows);
    std::swap(m_columns, matrix.m_columns);
    std::swap(m_elements, matrix.m_elements);
}

template <typename T>
Matrix<T>::~Matrix()
{
    for (unsigned int i = 0; i < m_rows; ++i) {
        delete [] m_elements[i];
    }

    delete [] m_elements;
}

template <typename T>
unsigned int Matrix<T>::rows() const
{
    return m_rows;
}

template <typename T>
unsigned int Matrix<T>::columns() const
{
    return m_columns;
}

template <typename T>
const int * Matrix<T>::operator[](unsigned int index) const
{
    if ( index >= m_rows ) {
        throw std::invalid_argument("index goes abroad");
    }

    return m_elements[index];
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix & matrix) const
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    if ( m_columns != matrix.m_rows ) {
        throw std::invalid_argument("matrix sizes do not match");
    }

    unsigned int n = m_rows;
    unsigned int m = matrix.m_columns;
    unsigned int s = m_columns;

    T **elements = new T *[n];
    for (unsigned int i = 0; i < n; ++i) {
        elements[i] = new T[m];
        for (unsigned int j = 0; j < m; ++j) {
            T value = 0;
            for (unsigned int k = 0; k < s; ++k) {
                value += m_elements[i][k] * matrix.m_elements[k][j];
            }
            elements[i][j] = value;
        }
    }

    return Matrix(n, m, elements);
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix & matrix) const
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    if ( m_rows != matrix.m_rows || m_columns != matrix.m_columns ) {
        throw std::invalid_argument("matrix sizes do not match");
    }

    unsigned int n = m_rows;
    unsigned int m = m_columns;

    T **data = new T *[n];
    for (unsigned int i = 0; i < n; ++i) {
        data[i] = new T[m];
        for (unsigned int j = 0; j < m; ++j) {
            data[i][j] = m_elements[i][j] + matrix.m_elements[i][j];
        }
    }

    return Matrix(n, m, data);
}

template <typename T>
bool Matrix<T>::operator==(const Matrix & matrix) const
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

template <typename T>
std::ostream & operator<<(std::ostream & output, const Matrix<T> & matrix)
{
  for (unsigned int i = 0; i < matrix.m_rows; ++i) {
    output << std::endl;
      for (unsigned int j = 0; j < matrix.m_columns; ++j) {
          output << matrix.m_elements[i][j] << "\t";
      }
  }

  return output;
}

template <typename T>
std::istream & operator>>(std::istream & input, Matrix<T> & matrix)
{
  for (unsigned int i = 0; i < matrix.m_rows; ++i) {
      for (unsigned int j = 0; j < matrix.m_columns; ++j) {
          if ( !(input >> matrix.m_elements[i][j]) ) {
              throw "exception in fill matrix";
          }
      }
  }

  return input;
}

#endif
