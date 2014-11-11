#include "matrix.h"

Matrix::Matrix():values_(NULL), rows_(0), cols(0) {}

Matrix::Matrix(const Matrix& m):values_(m.values_), rows_(m.rows()), cols_(m.cols()) {}

Matrix::Matrix(int rows, int cols)
{
    values_.reserve(rows*cols);
    rows_ = rows;
    cols_ = cols;
}

int& Matrix::operator()(int r, int c)
{
    return values_[r*rows_+c];
}

const int& Matrix::operator()(int r, int c) const
{
    return values_[r*rows_+c];
}

Matrix Matrix::operator+() const
{
    Matrix tmat(*this);
    return tmat;
}

Matrix Matrix::operator-() const
{
    Matrix tmat(*this);
    for(int i=0;i<tmat.rows_;i++)
    {
        for(int j=0;j<tmat.cols_;j++)
        {
            tmat(i,j) = -tmat(i,j);
        }
    }
    return tmat;
}

Matrix Matrix::Transpose() const
{
    Matrix tmat(cols_, rows_);
    for(int i=0;i<cols_;i++)
    {
        for(int j=0;j<rows_;j++)
        {
            tmat(i,j) = Sub2Ind(i, j);
        }
    }
    return tmat;
}

Vector::Vector(){}
Vector::Vector(const Vector& v)
{
    Matrix *tmat = &v;
    for(int i=0;i<v.rows();i++)
    {
        for(int j=0;j<v.cols();j++)
        {
            Matrix::(*tmat(i,j));
        }
    }
}

Vector::Vector(int rows)
{
    Matrix::Resize(rows, 1);
}

int Vector::rows() const
{
    return Matrix::rows();
}

int Vector::rows() const
{
    return Matrix::cols();
}

int& Vector:;operator[](int r)
{
    return Matrix::(r,0);
}

class Vector : public Matrix {

 public:

  int cols() const;

  void Resize(int rows);


  // [r]의 element를 리턴하는 연산자.

  int& operator[](int r);

  const int& operator()(int r) const;

};


// 입력 형식은 아래 설명 참고.

istream& operator>>(istream& is, Matrix& m);

istream& operator>>(istream& is, Vector& v);

ostream& operator<<(ostream& os, const Matrix& m);


// 행렬연산. 왼쪽 행렬과 오른쪽 행렬의 크기가 맞지 않아 계산이 되지 않는 경우

// cout << "Invalid operation" << endl; 을 출력하고 프로그램을 종료

// (exit(0) 함수).


Matrix operator+(const Matrix& lm, const Matrix& rm);

Matrix operator-(const Matrix& lm, const Matrix& rm);

// 행렬곱. 왼쪽 행렬의 행의 크기와 오른쪽 행렬의 열의 크기가 맞아야 함.

Matrix operator*(const Matrix& lm, const Matrix& rm);


Matrix operator+(const int& a, const Matrix& rm);

Matrix operator-(const int& a, const Matrix& rm);

Matrix operator*(const int& a, const Matrix& rm);

Matrix operator+(const Matrix& lm, const int& a);

Matrix operator-(const Matrix& lm, const int& a);
Matrix operator*(const Matrix& lm, const int& a);
