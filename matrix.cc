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


  // [r]�� element�� �����ϴ� ������.

  int& operator[](int r);

  const int& operator()(int r) const;

};


// �Է� ������ �Ʒ� ���� ����.

istream& operator>>(istream& is, Matrix& m);

istream& operator>>(istream& is, Vector& v);

ostream& operator<<(ostream& os, const Matrix& m);


// ��Ŀ���. ���� ��İ� ������ ����� ũ�Ⱑ ���� �ʾ� ����� ���� �ʴ� ���

// cout << "Invalid operation" << endl; �� ����ϰ� ���α׷��� ����

// (exit(0) �Լ�).


Matrix operator+(const Matrix& lm, const Matrix& rm);

Matrix operator-(const Matrix& lm, const Matrix& rm);

// ��İ�. ���� ����� ���� ũ��� ������ ����� ���� ũ�Ⱑ �¾ƾ� ��.

Matrix operator*(const Matrix& lm, const Matrix& rm);


Matrix operator+(const int& a, const Matrix& rm);

Matrix operator-(const int& a, const Matrix& rm);

Matrix operator*(const int& a, const Matrix& rm);

Matrix operator+(const Matrix& lm, const int& a);

Matrix operator-(const Matrix& lm, const int& a);
Matrix operator*(const Matrix& lm, const int& a);
