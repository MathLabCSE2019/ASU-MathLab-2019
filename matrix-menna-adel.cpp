#include "mathlab.h"
#include <cstdarg>
#include <iostream>
#include <string>
#include <algorithm>
#include "stdio.h"
#include <cstring>
#include <cstdlib>
#include <math.h>
#include <complex>

using namespace std;

CMatrix::CMatrix(){
	nR = nC = 0;
	values = NULL;
}
CMatrix::~CMatrix(){
	
}
CMatrix::CMatrix(int nR, int nC, int initialization, double initializationValue){
	this->nR = nR; this->nC = nC;
	if ((nR*nC) == 0){
		values = NULL;
		return;
	}values = new double*[nR];
	for (int iR = 0; iR<nR; iR++){
		values[iR] = new double[nC];
		for (int iC = 0; iC<nC; iC++){
			switch (initialization){
			case MI_ZEROS: values[iR][iC] = 0;
				break;
			case MI_ONES: values[iR][iC] = 1;
				break;
			case MI_EYE: values[iR][iC] = (iR == iC) ? 1 : 0;
				break;
			case MI_RAND: values[iR][iC] = (rand() % 1000000) / 1000000.0;
				break;
			case MI_VALUE: values[iR][iC] = initializationValue;
				break;
			}
		}
	}
}
CMatrix::CMatrix(int nR, int nC, double first, ...){
	this->nR = nR;
	this->nC = nC;
	if ((nR*nC) == 0){
		values = NULL;
		return;
	}
	values = new double*[nR];
	va_list va; va_start(va, first);
	for (int iR = 0; iR<nR; iR++){
	values[iR] = new double[nC];
	for (int iC = 0; iC<nC; iC++){
	values[iR][iC] = (iC == 0 && iR == 0) ? first : va_arg(va, double);
	}
	}
	va_end(va);
}

CMatrix::CMatrix(CMatrix& m){
	nR = nC = 0;
	values = NULL;
	copy(m);
}

//-----------------------------------SinFunction---------------------------------------
void CMatrix::Sin(CMatrix& matrix)
{
    for(int i=0 ; i<nR ; i++)
    {
        for(int j=0 ; j<nC ; j++)
        {
            values[i][j] = sin(matrix.values[i][j]);
        }
    }

}
//-----------------------------------CosFunction---------------------------------------
void CMatrix::Cos(CMatrix& matrix)
{
    for(int i=0 ; i<nR ; i++)
    {
        for(int j=0 ; j<nC ; j++)
        {
            values[i][j] = cos(matrix.values[i][j]);
        }
    }

}
//-----------------------------------TanFunction---------------------------------------
void CMatrix::Tan(CMatrix& matrix)
{
    for(int i=0 ; i<nR ; i++)
    {
        for(int j=0 ; j<nC ; j++)
        {
            values[i][j] = tan(matrix.values[i][j]);
        }
    }

}
//---------------------------------CscFunction----------------------------------------
void CMatrix::Csc(CMatrix& matrix)
{
    for(int i=0 ; i<nR ; i++)
    {
        for(int j=0 ; j<nC ; j++)
        {
           values[i][j] = 1/sin(matrix.values[i][j]);
        }
    }

}
    //---------------------------------SecFunction----------------------------------------
void CMatrix::Sec(CMatrix& matrix)
{
    for(int i=0 ; i<nR ; i++)
    {
        for(int j=0 ; j<nC ; j++)
        {
           values[i][j] = 1/cos(matrix.values[i][j]);
        }
    }

}
    //---------------------------------CotFunction----------------------------------------
void CMatrix::Cot(CMatrix& matrix)
{
    for(int i=0 ; i<nR ; i++)
    {
        for(int j=0 ; j<nC ; j++)
        {
           values[i][j] = 1/tan(matrix.values[i][j]);
        }
    }

}
 //-----------------------------------------------SindFunction------------------------------------
void CMatrix::Sind(CMatrix& matrix)
{
    float pi = 3.141592654;
    for(int i=0 ; i<nR ; i++)
    {
        for(int j=0 ; j<nC ; j++)
        {
           values[i][j] = sin((pi/180)*matrix.values[i][j]);
        }
    }

}
//-----------------------------------------------CscdFunction----------------------------------------------------
void CMatrix::Cscd(CMatrix& matrix)
{
    float pi = 3.141592654;
    for(int i=0 ; i<nR ; i++)
    {
        for(int j=0 ; j<nC ; j++)
        {
            values[i][j] = 1/sin((pi/180)*matrix.values[i][j]);
        }
    }

}
//-----------------------------------------------CosdFunction---------------------------------
void CMatrix::Cosd(CMatrix& matrix)
{
    float pi = 3.141592654;
    for(int i=0 ; i<nR ; i++)
    {
        for(int j=0 ; j<nC ; j++)
        {
            values[i][j] = cos((pi/180)*matrix.values[i][j]);
        }
    }

}
//-----------------------------------------------SecdFunction---------------------------------------------------
void CMatrix::Secd(CMatrix& matrix)
{
    float pi = 3.141592654;
    for(int i=0 ; i<nR ; i++)
    {
        for(int j=0 ; j<nC ; j++)
        {
            values[i][j] = 1/cos((pi/180)*matrix.values[i][j]);
        }
    }

}
//-----------------------------------------------TandFunction----------------------------------------------------
void CMatrix::Tand(CMatrix& matrix)
{
    float pi = 3.141592654;
    for(int i=0 ; i<nR ; i++)
    {
        for(int j=0 ; j<nC ; j++)
        {
            values[i][j] = tan((pi/180)*values[i][j]);
        }
    }

}
//-----------------------------------------------CotdFunction----------------------------------------------------
void CMatrix::Cotd(CMatrix& matrix)
{
    float pi = 3.141592654;
    for(int i=0 ; i<nR ; i++)
    {
        for(int j=0 ; j<nC ; j++)
        {
            values[i][j] = 1/tan((pi/180)*matrix.values[i][j]);
        }
    }

}
//--------------------------------------------asinFunction------------------------------------------------------
void CMatrix::aSin(CMatrix& matrix)
{
    for(int i=0 ; i<nR ; i++)
    {
        for(int j=0 ; j<nC ; j++)
        {
            values[i][j] = asin(matrix.values[i][j]);
        }
    }
}
 //--------------------------------------------acosFunction------------------------------------------------------
void CMatrix::aCos(CMatrix& matrix)
{
    for(int i=0 ; i<nR ; i++)
    {
        for(int j=0 ; j<nC ; j++)
        {
            values[i][j] = acos(matrix.values[i][j]);
        }
    }
}
//--------------------------------------------atanFunction------------------------------------------------------
void CMatrix::aTan(CMatrix& matrix)
{
    for(int i=0 ; i<nR ; i++)
    {
        for(int j=0 ; j<nC ; j++)
        {
            values[i][j] = atan(matrix.values[i][j]);
        }
    }
}
 //--------------------------------------------asecFunction------------------------------------------------------
void CMatrix::aSec(CMatrix& matrix)
{
    for(int i=0 ; i<nR ; i++)
    {
        for(int j=0 ; j<nC ; j++)
        {
            values[i][j] = acos(matrix.values[i][j]);
        }
    }
}
//--------------------------------------------acscFunction------------------------------------------------------
void CMatrix::aCsc(CMatrix& matrix)
{
    for(int i=0 ; i<nR ; i++)
    {
        for(int j=0 ; j<nC ; j++)
        {
            values[i][j] = asin(1/matrix.values[i][j]);
        }
    }
}
//--------------------------------------------acotFunction------------------------------------------------------
void CMatrix::aCot(CMatrix& matrix)
{
    for(int i=0 ; i<nR ; i++)
    {
        for(int j=0 ; j<nC ; j++)
        {
            values[i][j] = atan(1/matrix.values[i][j]);
        }
    }
}

























