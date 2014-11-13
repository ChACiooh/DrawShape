#include "matrix.h"
#include <cstdlib>

/*** Definitions of Matrix and its instances ***/
Matrix::Matrix():values_(), rows_(0), cols_(0) {}

Matrix::Matrix(const Matrix& m):values_(m.values_), rows_(m.rows()), cols_(m.cols()) {}

Matrix::Matrix(int rows, int cols)
{
    values_.resize(rows*cols);
    rows_ = rows;
    cols_ = cols;
}

int& Matrix::operator()(int r, int c)
{
    size_t idx = r*cols_+c;
    if(idx>=values_.size()) return OUT_OF_RANGE;
    return values_[idx];
}

const int& Matrix::operator()(int r, int c) const
{
    size_t idx = r*cols_+c;
    if(idx>=values_.size()) return OUT_OF_RANGE;
    return values_[idx];
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
        for(int j=0;j<rows_;j++)
            tmat(i,j) = Matrix::operator()(j, i);
    return tmat;
}


/*** Definitions of Vector's functions ***/
Vector::Vector(){}
Vector::Vector(const Vector& v):Matrix(v.rows(), v.cols()) {}

Vector::Vector(int rows)
{
    Matrix::Resize(rows, 1);
}

int Vector::rows() const
{
    return Matrix::rows();
}

int Vector::cols() const
{
    return Matrix::cols();
}

void Vector::Resize(int rows)
{
    Matrix::Resize(rows, 1);
}

int& Vector::operator[](int r)
{
    return Matrix::operator()(r,0);
}

const int& Vector::operator()(int r) const
{
    return Matrix::operator()(r,0);
}
// 입력 형식은 아래 설명 참고.

/*** operator overloading ***/
istream& operator>>(istream& is, Matrix& m)
{
    int rows, cols;
    is >> rows >> cols;
    m.Resize(rows, cols);
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            int num;
            is >> num;
            m(i,j) = num;
        }
    }
    return is;
}

istream& operator>>(istream& is, Vector& v)
{
    int rows;
    is >> rows;
    v.Resize(rows);
    for(int i=0;i<rows;i++)
    {
        int num;
        is >> num;
        v[i] = num;
    }
    return is;
}

ostream& operator<<(ostream& os, const Matrix& m)
{
    for(int i=0;i<m.rows();i++)
    {
        for(int j=0;j<m.cols();j++) os << m(i,j) << " ";
        os << endl;
    }
    return os;
}

/*** 행렬연산. 왼쪽 행렬과 오른쪽 행렬의 크기가 맞지 않아 계산이 되지 않는 경우
     cout << "Invalid operation" << endl; 을 출력하고 프로그램을 종료
     (exit(0) 함수).
***/
void DifAmpMat(int r1, int c1, int r2, int c2)
{
    if(r1 != r2 || c1 != c2)
    {
        cout << "Invalid operation" << endl;
        exit(0);
    }
}

void DifAmpMat(int left_col, int right_row)
{
    if(left_col != right_row)
    {
        cout << "Invalid operation" << endl;
        exit(0);
    }
}

Matrix operator+(const Matrix& lm, const Matrix& rm)
{
    int r1, c1, r2, c2;
    r1 = lm.rows(); c1 = lm.cols();
    r2 = rm.rows(); c2 = rm.cols();
    DifAmpMat(r1, c1, r2, c2);

    Matrix result_mat(r1, c1);
    for(int i=0;i<r1;i++)
    {
        for(int j=0;j<c1;j++)
        {
            result_mat(i,j) = lm(i,j)+rm(i,j);
        }
    }
    return result_mat;
}

Matrix operator-(const Matrix& lm, const Matrix& rm)
{
    int r1, c1, r2, c2;
    r1 = lm.rows(); c1 = lm.cols();
    r2 = rm.rows(); c2 = rm.cols();
    DifAmpMat(r1, c1, r2, c2);

    Matrix result_mat(r1, c1);
    for(int i=0;i<r1;i++)
    {
        for(int j=0;j<c1;j++)
        {
            result_mat(i,j) = lm(i,j)-rm(i,j);
        }
    }
    return result_mat;
}

// 행렬곱. 왼쪽 행렬의 행의 크기와 오른쪽 행렬의 열의 크기가 맞아야 함.

Matrix operator*(const Matrix& lm, const Matrix& rm)
{
    int left_col, right_row;
    left_col = lm.cols();
    right_row = rm.rows();
    DifAmpMat(left_col, right_row);

    int r_col, r_row;
    r_col = rm.cols();
    r_row = lm.rows();
    Matrix result_mat(r_row, r_col);
    for(int i=0;i<r_row;i++)
    {
        for(int j=0;j<r_col;j++)
        {
            result_mat(i,j) = 0;
            for(int k=0;k<left_col;k++)
            {
                //cout << "res("<<i<<","<<j<<")+="<<lm(i,k)<<"*"<<rm(k,j)<<endl;
                result_mat(i,j) += lm(i,k) * rm(k,j);
                //cout << "(" << i << "," << j << ")=" << result_mat(i,j) << endl;
            }
            //cout << result_mat;
        }
    }
    return result_mat;
}


Matrix operator+(const int& a, const Matrix& rm)
{
    Matrix result_mat(rm);
    for(int i=0;i<result_mat.rows();i++)
        for(int j=0;j<result_mat.cols();j++)
            result_mat(i,j) += a;
    return result_mat;
}

Matrix operator-(const int& a, const Matrix& rm)
{
    Matrix result_mat(rm);
    for(int i=0;i<result_mat.rows();i++)
        for(int j=0;j<result_mat.cols();j++)
            result_mat(i,j) -= a;
    return result_mat;
}

Matrix operator*(const int& a, const Matrix& rm)
{
    Matrix result_mat(rm);
    for(int i=0;i<result_mat.rows();i++)
        for(int j=0;j<result_mat.cols();j++)
            result_mat(i,j) *= a;
    return result_mat;
}

Matrix operator+(const Matrix& lm, const int& a)
{
    Matrix result_mat(lm);
    for(int i=0;i<result_mat.rows();i++)
        for(int j=0;j<result_mat.cols();j++)
            result_mat(i,j) += a;
    return result_mat;
}

Matrix operator-(const Matrix& lm, const int& a)
{
    Matrix result_mat(lm);
    for(int i=0;i<result_mat.rows();i++)
        for(int j=0;j<result_mat.cols();j++)
            result_mat(i,j) -= a;
    return result_mat;
}

Matrix operator*(const Matrix& lm, const int& a)
{
    Matrix result_mat(lm);
    for(int i=0;i<result_mat.rows();i++)
        for(int j=0;j<result_mat.cols();j++)
            result_mat(i,j) *= a;
    return result_mat;
}
