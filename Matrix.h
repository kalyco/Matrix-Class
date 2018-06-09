// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>

class Matrix
{
 public:
	Matrix();

	Matrix(int row, int col);

	Matrix(const Matrix & other);

  Matrix & operator=(const Matrix & other);

	~Matrix();

  void input(std::istream & s = std::cin);
  void output(std::ostream & s = std::cout) const;

	int getVal(int r, int c) const;
	void setVal(int r, int c, int v);

	const int & operator[](int which) const;
  int & operator[](int which);

	int rLen;
	int cLen;
  int length() const;
	int getVal(const int& r, const int& c);

	private:
		int **mM;
		int * row;
		int * col;

  void allocate(int r, int c);
  void copy(const Matrix & other);
  void cleanup();
	void indexCheck(int i, int idx) const;
};

std::istream & operator>>(std::istream & s,       Matrix & a);
std::ostream & operator<<(std::ostream & s, const Matrix & a);
Matrix operator+(const Matrix & a2, const Matrix & a3);
Matrix operator*(const Matrix & a2, const Matrix & a3);

#endif