#pragma once

#include <iostream>
#include <string>
#include <algorithm>
//#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
//#include <cstring>
//#include <cstdlib>
#include <cmath>
//#include <cstdarg>
#define Co exp(-10)


using namespace std;
enum MI{ MI_ZEROS, MI_ONES, MI_EYE, MI_RAND, MI_VALUE };

class CMatrix{
	int nR, nC;
	double** values;
public:

    /**_____________________________________________**/
    /**____________ Matrix Constructors_____________**/
    /**_____________________________________________**/

	CMatrix();

	~CMatrix();

	CMatrix(int nR, int nC, int initialization = MI_ZEROS, double initializationValue = 0.0);

	CMatrix(int nR, int nC, double first, ...);

	CMatrix(const CMatrix& m);
	//CMatrix(CMatrix m);

	CMatrix(double d);

	CMatrix(string s);


    /**_____________________________________________**/
    /**________Matrix Private Members Access________**/
    /**_____________________________________________**/

	int getn(){ return nR*nC; };

	int getnR(){ return nR; };

	int getnC(){ return nC; };




    /**_____________________________________________**/
    /**_________Matrix Equality Operations__________**/
    /**_____________________________________________**/

	CMatrix operator=(const CMatrix& m);

	CMatrix& operator=(double d);

	CMatrix operator=(string s);

	void copy(const CMatrix& m);

	void copy(double d);

	void copy(string s);



    /**_____________________________________________**/
    /**________ Matrix Addition Operation___________**/
    /**_____________________________________________**/

	void add(CMatrix m);

	void operator+=(CMatrix m);

	void operator+=(double d);

	CMatrix operator+(CMatrix m);

	CMatrix operator+(double d);

	//C = plus(A,B); or C = A + B;


    /**_____________________________________________**/
    /**________ Matrix Subtraction Operation________**/
    /**_____________________________________________**/


	void sub(CMatrix m);

	void operator-=(CMatrix m);

	void operator-=(double d);

	CMatrix operator-(CMatrix m);

	CMatrix operator-(double d);


    /**________________________________________________**/
    /**________ Matrix Multiplication Operation________**/
    /**________________________________________________**/


	void mul(CMatrix m);

	void operator*=(CMatrix m);

	void operator*=(double d);

	CMatrix operator*(CMatrix m);

	CMatrix operator*(double d);

	CMatrix element_mul(CMatrix& another_matrix);


    /**_____________________________________________**/
    /**__________Matrix Division Operation__________**/
    /**_____________________________________________**/


	void operator/=(CMatrix another_matrix);

	void operator/=(double d);

	CMatrix operator/(CMatrix another_matrix);

	CMatrix operator/(double d);

	CMatrix element_div(CMatrix& another_matrix);

	CMatrix element_div(double a);


    /**_____________________________________________**/
    /**______________Matrix Increment_______________**/
    /**_____________________________________________**/


	CMatrix operator++(); //Pre Increment

	CMatrix operator++(int); //Post Increment, int is not used

	CMatrix operator--(); //Pre Increment

	CMatrix operator--(int); //Post Increment, int is not used



	/** signed matrix **/

	CMatrix operator-();

	CMatrix operator+();

    /**_____________________________________________**/
    /**_____________Matrix I/O Stream ______________**/
    /**_____________________________________________**/


	friend istream& operator >> (istream &is, CMatrix& C);
	//Stream
	friend ostream& operator << (ostream &os, CMatrix& C);
	//Stream

    /**_____________________________________________**/
    /**_____________Matrix Manipulation_____________**/
    /**_____________________________________________**/

    	void print();

	void reset();

	string getString();

	void setSubMatrix(int iR, int iC, CMatrix& m);

	CMatrix getSubMatrix(int r, int c, int nr, int nc);

	void addColumn(CMatrix& m);

	void addRow(CMatrix& m);

	CMatrix getCofactor(int r, int c);


	double& operator[](int i){ return values[i / nC][i%nC]; }

	double& operator()(int i){ return values[i / nC][i%nC]; }

	double& operator()(int r, int c){ return values[r][c]; }





    /**_____________________________________________**/
    /**__________Matrix Advanced Operation__________**/
    /**_____________________________________________**/


	double getDeterminant();

	CMatrix getTranspose();

	CMatrix getInverse();

    	void sweep(int a,int b);

    	void fix(int &a,int &b,int &s);

    	void swap(int a,int b);

	
    /**_____________________________________________**/
    /**___________Matrix Power Operation____________**/
    /**_____________________________________________**/

    	CMatrix operator^(int);//matrix power operator

    	CMatrix mpower(double);//elements power

    	CMatrix power(int);//matrix power



    /**________________________________________________**/
    /**_________ Matrix Logarithmic Operation__________**/
    /**________________________________________________**/

    	CMatrix mlog10(); //log function to the base 10

    	CMatrix mlog2(); //log function to the base 2

    	CMatrix mlog(); //log function (ln)	
	
	

    /**________________________________________________**/
    /**_________Matrix Trignometric Operation__________**/
    /**________________________________________________**/

    	friend CMatrix Sin(CMatrix matrix);

    	friend CMatrix Cos(CMatrix matrix);

    	friend CMatrix Tan(CMatrix matrix);

    	friend CMatrix Csc(CMatrix matrix);

    	friend CMatrix Sec(CMatrix matrix);

    	friend CMatrix Cot(CMatrix matrix);

    	friend CMatrix Sind(CMatrix matrix);

    	friend CMatrix Cosd(CMatrix matrix);

    	friend CMatrix Tand(CMatrix matrix);

    	friend CMatrix Cscd(CMatrix matrix);

    	friend CMatrix Secd(CMatrix matrix);

    	friend CMatrix Cotd(CMatrix matrix);

	friend CMatrix aSin(CMatrix matrix);

	friend CMatrix aCos(CMatrix matrix);

	friend CMatrix aTan(CMatrix matrix);

	friend CMatrix aCsc(CMatrix matrix);

	friend CMatrix aSec(CMatrix matrix);

	friend CMatrix aCot(CMatrix matrix);

    	friend CMatrix squareRoot(CMatrix matrix);

    	//void sqrtm(CMatrix& matrix);

	void addMatrixHor(CMatrix& c);
	void addMatrixVer(CMatrix& c);

};


    /**_____________________________________________**/
    /**___________Matrix Outer Operation____________**/
    /**_____________________________________________**/


CMatrix mrand(int R = 1 , int C = 0);

CMatrix eye(int R = 1 , int C = 0);

CMatrix zeros(int R = 1 , int C = 0);

CMatrix ones(int R = 1 , int C = 0);
