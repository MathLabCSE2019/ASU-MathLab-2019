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

}

//=======================================SquareRootForAllMatrix================================================
void CMatrix:: sqrtm(CMatrix& matrix)
{
     struct matrix
    {
    double real;
    double imag;
    };
    //----------------------Calculate the race and Determinant----------------------------
    double Trace = values[0][0]+values[1][1];
    double Determinant = values[0][0]*values[1][1]-values[0][1]*values[1][0];
    //----------------------Calculate EigenValues-----------------------------------------
    matrix eigenValue1;
    matrix eigenValue2;
    double square = (pow(Trace,2)/4)-Determinant;
    if(square > 0)
    {
    eigenValue1.real = (Trace/2)+sqrt(square);
    eigenValue2.real = (Trace/2)-sqrt(square);
    eigenValue1.imag = 0;
    eigenValue2.imag = 0;
    }
    else if(square < 0)
    {
    square *= -1;
    eigenValue1.imag = (Trace/2)+sqrt(square);
    eigenValue2.imag = (Trace/2)-sqrt(square);
    eigenValue1.real = 0;
    eigenValue2.real = 0;
    }
    else
    {
    eigenValue1.real = (Trace/2);
    eigenValue2.real = (Trace/2);
    }
    //----------------------Calculate firstEigenVector------------------------------------
    matrix **eigenVector1 = new matrix*[nR];
    for(int i=0;i<nR;i++)
    {
        eigenVector1[i] = new matrix[1];
        for(int j=0;j<1;j++)
        {
            eigenVector1[i][j].real = 0;
            eigenVector1[i][j].imag = 0;
        }
    }
    eigenVector1[0][0].real = eigenValue1.real-values[1][1];
    eigenVector1[0][0].imag = eigenValue1.imag;
    eigenVector1[1][0].real = values[1][0];
    //----------------------secondEigenVector---------------------------------------------
     matrix **eigenVector2 = new matrix*[nR];
    for(int i=0;i<nR;i++)
    {
        eigenVector2[i] = new matrix[1];
        for(int j=0;j<1;j++)
        {
            eigenVector2[i][j].real = 0;
            eigenVector2[i][j].imag = 0;
        }
    }
    eigenVector2[0][0].real = eigenValue2.real-values[1][1];
    eigenVector2[0][0].imag = eigenValue2.imag;
    eigenVector2[1][0].real = values[1][0];
    //----------------------------------eigenVectorMatrix----------------------------------
      matrix **eigenVectorMatrix = new matrix*[nR];
    for(int i=0;i<nR;i++)
    {
        eigenVectorMatrix[i] = new matrix[nC];
         for(int j=0;j<nC;j++)
        {
            eigenVectorMatrix[i][j].real = 0;
            eigenVectorMatrix[i][j].imag = 0;
        }
    }
    eigenVectorMatrix[0][0].real = eigenVector1[0][0].real;
    eigenVectorMatrix[0][0].imag = eigenVector1[0][0].imag;
    eigenVectorMatrix[1][0].real = eigenVector1[1][0].real;
    eigenVectorMatrix[1][0].imag = eigenVector1[1][0].imag;
    eigenVectorMatrix[0][1].real = eigenVector2[0][0].real;
    eigenVectorMatrix[0][1].imag = eigenVector2[0][0].imag;
    eigenVectorMatrix[1][1].real = eigenVector2[1][0].real;
    eigenVectorMatrix[1][1].imag = eigenVector2[1][0].imag;
    //----------------------------------eigenValuesMatrix---------------------------------------------
    matrix **eigenValuesMatrix = new matrix*[nR];
    for(int i=0;i<nR;i++)
    {
         eigenValuesMatrix[i] = new matrix[nC];
         for(int j=0;j<nC;j++)
         {
            eigenValuesMatrix[i][j].real = 0;
            eigenValuesMatrix[i][j].imag = 0;
         }
    }
    eigenValuesMatrix[0][0].real = real(sqrt(complex<double>(eigenValue1.real, eigenValue1.imag)));
    eigenValuesMatrix[0][0].imag = imag(sqrt(complex<double>(eigenValue1.real, eigenValue1.imag)));
    eigenValuesMatrix[1][1].real = real(sqrt(complex<double>(eigenValue2.real, eigenValue2.imag)));
    eigenValuesMatrix[1][1].imag = imag(sqrt(complex<double>(eigenValue2.real, eigenValue2.imag)));
    //----------------------------------eigenVectorsInverseMatrix---------------------------------------------
      matrix **eigenVectorsInverseMatrix = new matrix*[nR];
    for(int i=0;i<nR;i++)
    {
        eigenVectorsInverseMatrix[i] = new matrix[nC];
        for(int j=0;j<nC;j++)
        {
            eigenVectorsInverseMatrix[i][j].real = 0;
            eigenVectorsInverseMatrix[i][j].imag = 0;
        }
    }
    matrix DeterminantForInverse,DInverse;
    DeterminantForInverse.real = ((eigenVectorMatrix[0][0].real*eigenVectorMatrix[1][1].real)-(eigenVectorMatrix[0][0].imag*eigenVectorMatrix[1][1].imag))- ((eigenVectorMatrix[0][1].real*eigenVectorMatrix[1][0].real)-(eigenVectorMatrix[0][1].imag*eigenVectorMatrix[1][0].imag));
    DeterminantForInverse.imag = ((eigenVectorMatrix[0][0].real*eigenVectorMatrix[1][1].imag)+(eigenVectorMatrix[0][0].imag*eigenVectorMatrix[1][1].real))-((eigenVectorMatrix[0][1].real*eigenVectorMatrix[1][0].imag)+(eigenVectorMatrix[0][1].imag*eigenVectorMatrix[1][0].real));
    complex <double> z (DeterminantForInverse.real,DeterminantForInverse.imag);
    DInverse.real = real(pow(z,-1));
    DInverse.imag = imag(pow(z,-1));
    eigenVectorsInverseMatrix[0][0].real = ((DInverse.real*eigenVectorMatrix[1][1].real)-(DInverse.imag*eigenVectorMatrix[1][1].imag));
    eigenVectorsInverseMatrix[0][0].imag = ((DInverse.real*eigenVectorMatrix[1][1].imag)+(DInverse.imag*eigenVectorMatrix[1][1].real));
    eigenVectorsInverseMatrix[1][0].real = ((DInverse.real*eigenVectorMatrix[1][0].real)-(DInverse.imag*eigenVectorMatrix[1][0].imag))*(-1);
    eigenVectorsInverseMatrix[1][0].imag = ((DInverse.real*eigenVectorMatrix[1][0].imag)+(DInverse.imag*eigenVectorMatrix[1][0].real))*(-1);
    eigenVectorsInverseMatrix[0][1].real = ((DInverse.real*eigenVectorMatrix[0][1].real)-(DInverse.imag*eigenVectorMatrix[0][1].imag))*(-1);
    eigenVectorsInverseMatrix[0][1].imag = ((DInverse.real*eigenVectorMatrix[0][1].imag)+(DInverse.imag*eigenVectorMatrix[0][1].real))*(-1);
    eigenVectorsInverseMatrix[1][1].real = ((DInverse.real*eigenVectorMatrix[0][0].real)-(DInverse.imag*eigenVectorMatrix[0][0].imag));
    eigenVectorsInverseMatrix[1][1].imag = ((DInverse.real*eigenVectorMatrix[0][0].imag)+(DInverse.imag*eigenVectorMatrix[0][0].real));
    //----------------------------------Result-----------------------------------------
     matrix **Result1 = new matrix*[nR];
    for(int i=0;i<nR;i++)
    {
        Result1[i] = new matrix[nC];
         for (int j = 0; j < nC; j++)
        {
            Result1[i][j].real = 0;
            Result1[i][j].imag = 0;
        }
    }
     for (int i = 0; i < nR; i++)
    {
        for (int j = 0; j < nC; j++)
        {

            for (int k = 0; k < nR; k++)
            {
                Result1[i][j].real += (eigenVectorMatrix[i][k].real * eigenValuesMatrix[k][j].real) - (eigenVectorMatrix[i][k].imag * eigenValuesMatrix[k][j].imag) ;
                Result1[i][j].imag += (eigenVectorMatrix[i][k].real * eigenValuesMatrix[k][j].imag) + (eigenVectorMatrix[i][k].imag * eigenValuesMatrix[k][j].real) ;
            }
        }

    }
     matrix **Result = new matrix*[nR];
    for(int i=0;i<nR;i++)
    {
        Result[i] = new matrix[nC];
           for (int j = 0; j < nC; j++)
        {
            Result[i][j].real = 0;
            Result[i][j].imag = 0;
        }
    }
     for (int i = 0; i < nR; i++)
    {
        for (int j = 0; j < nC; j++)
        {

            for (int k = 0; k < nR; k++)
            {
                 Result[i][j].real += (Result1[i][k].real * eigenVectorsInverseMatrix[k][j].real) - (Result1[i][k].imag * eigenVectorsInverseMatrix[k][j].imag) ;
                 Result[i][j].imag += (Result1[i][k].real * eigenVectorsInverseMatrix[k][j].imag) + (Result1[i][k].imag * eigenVectorsInverseMatrix[k][j].real) ;
            }
        }

    }
    //----------------------------------Printing the Result---------------------------------------------
    for(int i=0 ; i<nR ; i++)
    {
        for(int j=0 ; j<nC ; j++)
        {

            if(Result[i][j].imag>=0)
            {
            cout<<Result[i][j].real<<'+'<<Result[i][j].imag<<'i'<<"\t";
            }
            else if(Result[i][j].imag<0)
            {
            cout<<Result[i][j].real<<Result[i][j].imag<<'i'<<"\t";
            }
            else
            {
            cout<<Result[i][j].real<<'+'<<Result[i][j].imag<<'i'<<"\t";
            }
        }
        cout<<"\n";
    }

}
//-------------------------------------SquareRootElementByElement-------------------------------------------------
void CMatrix::Sqrt(CMatrix& matrix)
{
    for(int i=0 ; i<nR ; i++)
    {
        for(int j=0 ; j<nC ; j++)
        {
            values[i][j] = sqrt(matrix.values[i][j]);
        }
    }
}

