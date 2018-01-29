
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
	CMatrix(CMatrix& m);//
	CMatrix(double d);//
	void Sqrt(CMatrix& matrix);
  void sqrtm(CMatrix& matrix);
  











};
