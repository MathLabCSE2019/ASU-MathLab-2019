
#pragma once
#include <iostream>
#include "mathlab.h"
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>

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
	CMatrix(CMatrix& m);
  void Cotd(CMatrix& matrix);
	void Tand(CMatrix& matrix);
	void Secd(CMatrix& matrix);
	void Cosd(CMatrix& matrix);
	void Cscd(CMatrix& matrix);
	void Sind(CMatrix& matrix);
	void Cot(CMatrix& matrix);
	void Tan(CMatrix& matrix);
	void Sec(CMatrix& matrix);
	void Cos(CMatrix& matrix);
	void Csc(CMatrix& matrix);
	void Sin(CMatrix& matrix);
	void aSin(CMatrix& matrix);
	void aCos(CMatrix& matrix);
	void aTan(CMatrix& matrix);
	void aSec(CMatrix& matrix);
	void aCsc(CMatrix& matrix);
	void aCot(CMatrix& matrix);















};
