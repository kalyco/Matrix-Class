// Matrix.cpp

#include <iostream>
#include <cstdlib>
#include <fstream>

#include "Matrix.h"

Matrix::Matrix()
  : rLen(0), cLen(0), mM(NULL)
{
}

Matrix::Matrix(int r, int c)
{
  rLen = r;
  cLen = c;
	allocate(r, c);
}

Matrix::Matrix(const Matrix& other)
{
  copy(other);
}

Matrix::~Matrix()
{
  cleanup();
}

void Matrix::copy(const Matrix & other)
{
  allocate(other.rLen, other.cLen);

  for (int i = 0; i < length(); i++) {
    (*this)[i] = other[i];
  }
}

void Matrix::allocate(int r, int c)
{
  if (rLen < 0 || cLen < 0) {
    std::cout << "Negative index." << std::endl;
    return;
  }
	rLen = r;
	cLen = c;
  mM = new int*[rLen];
  for (int r=0; r < rLen; r++)
    mM[r] = new int[cLen];
}

////////////////////////////////
// Overloaded Operator functions
////////////////////////////////
const int & Matrix::operator[](int i) const
{
  indexCheck(i, rLen);
  return (*this)[i];
}

int & Matrix::operator[](int i)
{
  indexCheck(i, rLen);
  return (*this)[i];
}

Matrix& Matrix::operator=(const Matrix& other)
{
  if (this != &other) {
    cleanup();
    copy(other);
  }
  return *this;
}

// Overloaded operator>>: Read the number of rows,
// the number of columns and then the elements.
std::istream& operator>>(std::istream& s, Matrix& a)
{
  a.input(s);
  return s;
}

std::ostream& operator<<(std::ostream& s, const Matrix& a)
{
  a.output(s);
  return s;
}

Matrix operator+(const Matrix & a2, const Matrix & a3)
{
  if (a2.length() != a3.length()) {
    std::cout << "Inconsistent Matrix sizes." << std::endl;
    exit(1);
  }

  Matrix a1(a2.rLen, a2.cLen);
  int curRow = 0;
  int curCol = 0;
  for (int i = 0; i < a2.length(); i++) {
    int a2V = a2.getVal(curRow, curCol);
    int a3V = a3.getVal(curRow, curCol);
    a1.setVal(curRow, curCol, a2V + a3V);
    if (curCol == a2.cLen - 1){
    curCol = 0;
    curRow +=1;
		} else {
			curCol +=1;
		}
  }
  return a1;
}

Matrix operator*(const Matrix & a2, const Matrix & a3)
{
  if (a2.length() != a3.length()) {
    std::cout << "Inconsistent Matrix sizes." << std::endl;
    exit(1);
  }

  Matrix a1(a2.rLen, a2.cLen);
  int curRow = 0;
  int curCol = 0;
  // for each element of the matrix product  
  for (int i = 0; i < a2.length(); i++) {
    //TODO: clean this WAY up
    int total = 0;
    int rowV2 = 0;
    int colV2 = 0;
    int rowV3 = 0;
    int colV3 = 0;
    for (int x = 0; x < a2.rLen; x++) {
      // multiply the value ar2 rows by a3 cols.
      // increment row val, increment col val
      // repeat until end of index
      int a2V = a2.getVal(rowV2, colV2);
      int a3V = a3.getVal(rowV3, colV3);
      total += (a2V * a3V);
      colV3++;
      rowV2++;
    }
    a1.setVal(curRow, curCol, total);
    // if first row is all set, incr next row
    // otherwise incr col
    if (colV3 == (a3.cLen - 1)) {
      colV3 = 0;
      rowV2++;
    } else {
      rowV2--;
      colV3++;    
    }
    if (curCol == a2.cLen - 1){
    curCol = 0;
    curRow++;
		} else {
			curCol +=1;
		}
  }
  return a1;
}

////////////////////////////////
//     Class functions        //
////////////////////////////////

int Matrix::getVal(int r, int c) const {
  return mM[r][c];
}

void Matrix::setVal(int r, int c, int v) 
{
  mM[r][c] = v;
}

void Matrix::indexCheck(int i, int idx) const
{
  // TODO: Run this for everything
  if (i < 0 || i >= idx) {
    std::cout << "Invalid array index." << std::endl;
    exit(1);
  }
}

void Matrix::cleanup()
{
  for (int i = 0; i < (*this).length(); i++)
    delete[] mM[i];
}

int Matrix::length() const
{
  return rLen * cLen;
}

void Matrix::input(std::istream & s)
{
  std::ifstream infile("input.txt");
	std::string line;
  if (!mM) {
    std::cout << "Enter the number of rows: ";
    s >> rLen;
    std::cout << "Enter the number of columns: ";
    s >> cLen;
    allocate(rLen, cLen);
  }
	std::cout << "Enter the matrix:\n";
	int curRow = 0;
	int curCol = 0;
	for (int i=0; i < (*this).length(); i++) {
    // getline(infile, line);
		// int n = atoi(line.c_str());

    std::cout << "Matrix ";
    std::cout << "[" << curRow << "]" << "[" << curCol << "] = ";
    s >> mM[curRow][curCol];

		if (curCol == cLen - 1) { // if at last col, increment row, otherwise, increment col
			curCol = 0; // begin at next row
			curRow +=1;
		} else {
			curCol +=1; // continue
		}
	}
}

void Matrix::output(std::ostream & s) const
{
  int curRow = 0;
	int curCol = 0;
  for (int i = 0; i < (*this).length(); i++) {
    s << mM[curRow][curCol] << " ";
		if (curCol == cLen - 1) {
      s << std::endl;
			curCol = 0; // begin at next row
			curRow +=1;
		} else {
			curCol +=1; // continue
		}
  }
  s << std::endl;
}