#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <vector>

using namespace std;

class Matrix {

 public:

  Matrix();

  Matrix(const Matrix& m);

  Matrix(int rows, int cols);


  int rows() const { return rows_; }

  int cols() const { return cols_; }

  void Resize(int rows, int cols) {

    values_.resize((rows_ = rows) * (cols_ = cols));

  }


  // (r, c)�� element�� �����ϴ� ������.

  // ��) Matrix m(3,4);  cout << m(0,0) << "," << m(1,2); m(0,0) = 0;

  int& operator()(int r, int c);

  const int& operator()(int r, int c) const;


  Matrix operator+() const;  // ���׿����� (Unary operators)

  Matrix operator-() const;  // ex) Matrix m(2,3); cout << -m;


  Matrix Transpose() const;  // �Ʒ� ���� ����.


private:

  // ��� ���� �޾� �ش� ������ �迭 ���� ��ġ�� ����ϴ� �Լ�.

  int Sub2Ind(int r, int c) const { return r + c * rows_; }
  vector<int> values_;  // rows_ * cols_ ��ŭ�� ������ ���� �迭.
  int rows_, cols_;     // ��� ���� ����.
  // operator �Լ����� friend �� �������� ���� public �Լ��� �̿�.

};


class Vector : public Matrix {

 public:

  // Vector �� column�� ������ 1�� Matrix�� ��Ÿ������ �Ʒ� ����Լ� ����.

  Vector();

  Vector(const Vector& v);

  Vector(int rows);


  int rows() const;

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


#endif // MATRIX_H_INCLUDED
