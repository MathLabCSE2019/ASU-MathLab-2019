#include "matrix.h"
#include <cstdarg>
#include <iostream>
#include <string>
#include <algorithm>
#include "stdio.h"
#include <cstring>
#include <cstdlib>
#include <cmath>
#define Co exp(-10)
using namespace std;

CMatrix::CMatrix(){
	nR = nC = 0;
	values = NULL;
}
CMatrix::~CMatrix(){
	reset();
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
CMatrix::CMatrix(string s){
	nR = nC = 0;
	values = NULL;
	copy(s);
}

double CMatrix::getDeterminant(){
	if (nR != nC)throw("Invalid matrix dimension");
	if (nR == 1 && nC == 1)return values[0][0];
	double value = 1;
	int m = 1;
    int a=0,b=0;
    CMatrix d;
    d = *this;
    while(a<nR && b<nC)
	{
		d.fix(a,b,m);//basicall puts blank rows on the bottom
		d.sweep(a,b);//sweeps the column b taking a as pivot
		//advancing after sweeping
		a++;
		b++;
	}
     //cout<<endl<< "d="<<d<<endl;
	for (int iR = 0; iR<nR; iR++)
	{
		value*=d.values[iR][iR];
	}
    value*=m;
    return value;

}


void CMatrix:: getTranspose(CMatrix another_matrix)
{

    if(this != &another_matrix)
    {
       *this = another_matrix;
    }

    for(int r = 0 ; r < nR ; r++)
    {
        for(int c = 0 ; c < nC ; c++)
        {
            this->values[r][c] = another_matrix.values[c][r];
        }
    }
}

void CMatrix:: getInverse(CMatrix another_matrix)
{
    *this = another_matrix;
    double det = this->getDeterminant();
    if(!det) {cout<<"Invalid Matrix Operation";}
    else {
    double sign_correction = 1;
    for(int i = 0 ; i < nR ; i++)
    {
        for(int j = 0 ; j < nC ; j++)
        {
            this->values[i][j] = sign_correction * another_matrix.getCofactor(i,j).getDeterminant();
            sign_correction *= -1;
        }
    }
    *this /= det;
    this->getTranspose(*this);}
    int  sign_correction = 1;
    for(int i = 0 ; i < nR ; i++)
    {
        for(int j = 0 ; j < nC ; j++)
        {
            this->values[i][j] *= sign_correction;
            sign_correction *= -1;
        }}

}
void CMatrix:: div(CMatrix& m)
{
    m.getInverse(m);
    this->mul(m);

}

	void CMatrix::sweep(int a,int b)
{

	if (values[a][b] == 0)	//Checking whether the element is a valid pivot
		return;

	/*double divisor=values[a][b];//saving pivot values to a different variable as it it gets altered
	for(int j=0;j<nC;j++)
	{
		values[a][j]/=divisor;//making pivot 1
	}*/

	double factor=0.0;//number to multiply pivot with and subtract from corresponding rows
	for(int i=a+1;i<nR;i++)
	{
		if(i!=a)
		{
			factor=values[i][b]/values[a][b];//number to multiply pivot with and subtract from corresponding rows to sweep
			for(int j=0;j<nR;j++)
			{
				values[i][j]-=factor*values[a][j];//actual subtraction of each element of row i
			    if(abs(values[i][j]) < Co)
			    	values[i][j]=0.0;
			}
		}
	}

}


void CMatrix::fix(int &a,int &b,int &s)
{
	/*Simply swaps the first non zero row it finds incase element we are trying to use as pivot is 0 */
	while(values[a][b]==0 && a<nR && b<nC)
	{
		for(int i=a;i<nR;i++)
		{
			if(values[i][b]!=0)
			{
				this->swap(a,i);
				s=-s;
				return;
			}
		}
		b++;
	}
}

void CMatrix::swap(int a,int b)
{
	/*swaps row a and row b*/
	double temp=0;
	for(int j=0;j<nC;j++)
	{

		temp=values[a][j];
		values[a][j]=values[b][j];
		values[b][j]=temp;
	}
}

