#pragma once

#include <iostream>
#include <string>

using namespace std;
enum MI{ MI_ZEROS, MI_ONES, MI_EYE, MI_RAND, MI_VALUE };

class CMatrix{
	//int nR, nC;
	//double** values;
public:
    int nR, nC;
	double** values;
    void print();
	CMatrix();//
	~CMatrix();//
	//enum MI{ MI_ZEROS, MI_ONES, MI_EYE, MI_RAND, MI_VALUE };//
	CMatrix(int nR, int nC, int initialization = MI_ZEROS, double initializationValue = 0.0);//
	CMatrix(int nR, int nC, double first, ...);//
	CMatrix(CMatrix& m);//
	CMatrix(double d);//
	CMatrix(string s);//

	double getDeterminant();
	void getTranspose(CMatrix another_matrix);
	void getInverse(CMatrix another_matrix);
	void div(CMatrix& m);

	 void sweep(int a,int b);
	 void fix(int &a,int &b,int &s);
     void swap(int a,int b);


};
