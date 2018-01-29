#include "MathLap.h"
#include <cstdarg>
#include <iostream>
#include <string>
#include <algorithm>
#include "stdio.h"
#include <cstring>
#include <cstdlib>

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
void CMatrix::copy(const CMatrix& m){
    reset();
    this->nR = m.nR;
    this->nC = m.nC;
    if ((nR*nC) == 0){
        values = NULL;
        return;
    }
    values = new double*[nR];
    for (int iR = 0; iR<nR; iR++){
        values[iR] = new double[nC];
        for (int iC = 0; iC<nC; iC++){ values[iR][iC] = m.values[iR][iC]; }
    }
}
CMatrix::CMatrix(double d){
    nR = nC = 0;
    values = NULL;
    copy(d);
}
void CMatrix::copy(double d){
    reset();
    this->nR = 1;
    this->nC = 1;
    values = new double*[1];
    values[0] = new double[1];
    values[0][0] = d;
}
void CMatrix::copy(string s){
    reset();
    nR = count(s.begin(), s.end(), ';') + 1;
    nC = count(s.begin(), s.end(), ' ') / nR + 1;
    if ((nR*nC) == 0){ values = NULL; return; }
    values = new double*[nR];
    string token;
    for (int iR = 0; iR < nR; iR++)
    {
        values[iR] = new double[nC];
        for (int iC = 0; iC < nC; iC++)
        {
            string value;
            if (s.find("; ")<999999999999) {
            if (!(s.find(" ")) && !(s.find(";"))) {value = s.substr(1, s.find("]")); s.erase(1, s.find("]"));}
            else if (s.find(" ") < s.find(";")) {value = s.substr(1, s.find(" ")); s.erase(1, s.find(" "));}
            else {value = s.substr(1, s.find(";")); s.erase(1, s.find(";")+1);}
            values[iR][iC] = strtod(value.c_str(), NULL);}
            else {
            if (!(s.find(" ")) && !(s.find(";"))) token = "]";
            else if (s.find(" ") < s.find(";")) token = " ";
            else token = ";";
            value = s.substr(1, s.find(token)); s.erase(1, s.find(token));
            values[iR][iC] = strtod(value.c_str(), NULL);
            }
        }
    }


    //delete[] buffer;
}
void CMatrix::reset(){
    if (values){
        for (int i = 0; i<nR; i++)delete[] values[i];
        delete[] values;
    }
    nR = nC = 0;
    values = NULL;
}
string CMatrix::getString(){
    string s;
    for (int iR = 0; iR<nR; iR++){
        for (int iC = 0; iC<nC; iC++){
            char buffer[50];
            snprintf(buffer, 50, "%g\t", values[iR][iC]); s += buffer;
        }s += "\n";
    }return s;
}
CMatrix CMatrix::operator=(const CMatrix& m){
    copy(m);
    return *this;
}
CMatrix CMatrix::operator=(double d){
    copy(d);
    return *this;
}
CMatrix CMatrix::operator=(string s){ copy(s); return *this; }
void CMatrix::add(CMatrix& m){
    if (nR != m.nR || nC != m.nC)throw("Invalid matrix dimension");
    for (int iR = 0; iR<nR; iR++)for (int iC = 0; iC<nC; iC++)values[iR][iC] += m.values[iR][iC];
}
void CMatrix::operator+=(CMatrix& m){
    add(m);
}void CMatrix::operator+=(double d){
    CMatrix a(nR, nC, MI_VALUE, d);
    add(a);
}
CMatrix CMatrix::operator+(CMatrix& m){
    CMatrix r = *this; r += m; return r;
}
CMatrix CMatrix::operator+(double d){ CMatrix r = *this; r += d; return r; }
void CMatrix::sub(CMatrix& m){
    if (nR != m.nR || nC != m.nC)throw("Invalid matrix dimension");
    for (int iR = 0; iR<nR; iR++)for (int iC = 0; iC<nC; iC++)values[iR][iC] -= m.values[iR][iC];
}
void CMatrix::operator-=(CMatrix& m){ sub(m); }
void CMatrix::operator-=(double d){
    CMatrix h(nR, nC, MI_VALUE, d);
    sub(h);
}
CMatrix CMatrix::operator-(CMatrix& m){
    CMatrix r = *this; r -= m; return r;
}
CMatrix CMatrix::operator-(double d){ CMatrix r = *this; r -= d; return r; }
void CMatrix::mul(CMatrix& m){
    if (nR != m.nR || nC != m.nC)throw("Invalid matrix dimension");
    CMatrix r(nR, m.nC);
    for (int iR = 0; iR<r.nR; iR++)for (int iC = 0; iC<r.nC; iC++){
        r.values[iR][iC] = 0;
        for (int k = 0; k<m.nC; k++)r.values[iR][iC] += values[iR][k] * m.values[k][iC];
    }
    copy(r);
}
void CMatrix::operator*=(CMatrix& m){ mul(m); }
void CMatrix::operator*=(double d){
    for (int iR = 0; iR<nR; iR++)for (int iC = 0; iC<nC; iC++)values[iR][iC] *= d;
}
CMatrix CMatrix::operator*(CMatrix& m){ CMatrix r = *this; r *= m; return r; }
CMatrix CMatrix::operator*(double d){ CMatrix r = *this; r *= d; return r; }
CMatrix CMatrix::operator++(){
    CMatrix s(nR, nC, MI_VALUE, 1.0);
    add(s);
    return *this;
}
CMatrix CMatrix::operator++(int){
    CMatrix C = *this;
    CMatrix f(nR, nC, MI_VALUE, 1.0);
    add(f);
    return C;
}
CMatrix CMatrix::operator--(){
    CMatrix v(nR, nC, MI_VALUE, -1.0); add(v);
    return *this;
}
CMatrix CMatrix::operator--(int){
    CMatrix r = *this;
    CMatrix n(nR, nC, MI_VALUE, -1.0); add(n);
    return r;
}
CMatrix CMatrix::operator-(){
    for (int iR = 0; iR<nR; iR++)for (int iC = 0; iC<nC; iC++)values[iR][iC] = -values[iR][iC]; return *this;
}
CMatrix CMatrix::operator+(){ return *this; }
void CMatrix::setSubMatrix(int r, int c, CMatrix& m){
    if ((r + m.nR)>nR || (c + m.nC)>nC)throw("Invalid matrix dimension");
    for (int iR = 0; iR<m.nR; iR++)for (int iC = 0; iC<m.nC; iC++)values[r + iR][c + iC] = m.values[iR][iC];
}
CMatrix CMatrix::getSubMatrix(int r, int c, int nr, int nc){
    if ((r + nr)>nR || (c + nc)>nC)throw("Invalid matrix dimension");
    CMatrix m(nr, nc);
    for (int iR = 0; iR<m.nR; iR++)for (int iC = 0; iC<m.nC; iC++)m.values[iR][iC] = values[r + iR][c + iC]; return m;
}
void CMatrix::addColumn(CMatrix& m){
    CMatrix n(max(nR, m.nR), nC + m.nC);
    //errorrrr
    //n.setMatrix(0, 0, *this);
    //n.setMatrix(0, nC, m); *this = n;
}
void CMatrix::addRow(CMatrix& m){
    CMatrix n(nR + m.nR, max(nC, m.nC));
    //errrorr
    //n.setMatrix(0, 0, *this);
    //n.setMatrix(nR, 0, m); *this = n;
}
CMatrix CMatrix::getCofactor(int r, int c){
    if (nR <= 1 && nC <= 1)throw("Invalid matrix dimension");
    CMatrix m(nR - 1, nC - 1);
    for (int iR = 0; iR<m.nR; iR++)for (int iC = 0; iC<m.nC; iC++){
        int sR = (iR<r) ? iR : iR + 1;
        int sC = (iC<c) ? iC : iC + 1;
        m.values[iR][iC] = values[sR][sC];
    }
    return m;
}
double CMatrix::getDeterminant(){
    if (nR != nC)throw("Invalid matrix dimension");
    if (nR == 1 && nC == 1)return values[0][0];
    double value = 0, m = 1;
    for (int iR = 0; iR<nR; iR++){
        value += m * values[0][iR] * getCofactor(0, iR).getDeterminant();
        m *= -1;
    }return value;
}
istream& operator >> (istream &is, CMatrix& m){
    string s;
    CMatrix n(s);
    getline(is, s, ']'); s += "]";
    // not sure here **
    m.copy(n);
    return is;
}
ostream& operator << (ostream &os, CMatrix& m){
    os << m.getString(); return os;
}



void CMatrix::print()
{
    for (int iR = 0; iR < nR; iR++)
    for (int iC = 0; iC < nC; iC++)
        cout << values[iR][iC]<<endl;
}

//===========================

/** Matrix Division Operation **/
/*
CMatrix CMatrix:: operator/(CMatrix& another_matrix)
{
    if(nR != another_matrix.nR || nC != another_matrix.nC)
        throw("Invalid Matrix Dimention");
    CMatrix result_matrix(nR , nC);
    result_matrix = *this * (another_matrix.getInverse());

    return result_matrix;
}
*/

CMatrix CMatrix:: operator/(double number)
{

    CMatrix result_matrix(nR , nC);
    for(int i = 0 ; i < nR ; i++)
    {
        for(int j = 0 ; j < nC ; j++)
        {
            result_matrix.values[i][j] = values[i][j] / number ;
        }
    }
    return result_matrix;
}

/*
void CMatrix:: operator/=(CMatrix& another_matrix)
{
    if(nR != another_matrix.nR || nC != another_matrix.nC)
        throw("Invalid Matrix Dimention");
    *this *= another_matrix.getInverse();
}*/

void CMatrix:: operator/=(double number)
{
    for(int i = 0 ; i < nR ; i++)
    {
        for(int j = 0 ; j < nC ; j++)
        {
            values[i][j] /= number ;
        }
    }
}


CMatrix CMatrix :: element_div(CMatrix& another_matrix)
{
    if(nR != another_matrix.nR || nC != another_matrix.nC)
        throw("Invalid Matrix Dimension");

    CMatrix result_matrix(nR , nC);
    for(int i = 0 ; i < nR ; i++)
    {
        for(int j = 0 ; j < nC ; j++)
        {
            result_matrix.values[i][j] = values[i][j] / another_matrix.values[i][j] ;
        }
    }
    return result_matrix;
}
CMatrix CMatrix :: element_mul(CMatrix& another_matrix)
{
    if(nR != another_matrix.nR || nC != another_matrix.nC)
        throw("Invalid Matrix Dimension");

    CMatrix result_matrix(nR , nC);
    for(int i = 0 ; i < nR ; i++)
    {
        for(int j = 0 ; j < nC ; j++)
        {
            result_matrix.values[i][j] = values[i][j] * another_matrix.values[i][j] ;
        }
    }
    return result_matrix;
}
CMatrix CMatrix :: element_div(double a)
{
    CMatrix result_matrix(nR , nC);
    for(int i = 0 ; i < nR ; i++)
    {
        for(int j = 0 ; j < nC ; j++)
        {
            result_matrix.values[i][j] = a / values[i][j] ;
        }
    }
    return result_matrix;
}

/** Functions applied to dummy_matrix only **/



/*CMatrix CMatrix::getTranspose(CMatrix& another_matrix)
{
    CMatrix TransposeOfTheMatrix(another_matrix);
    for(int r = 0 ; r < another_matrix.nR ; r++)
        for(int c = 0 ; c < another_matrix.nC ; c++)
            another_matrix.values[r][c] = TransposeOfTheMatrix.values[c][r];
    return TransposeOfTheMatrix;
}*/


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
//-----------------------------------------SquareRootElementByElement---------------------------
void CMatrix::squareRoot(CMatrix& matrix)
{

    for(int i=0;i<nR;i++)
    {
        for(int j=0;j<nC;j++)
        {
            values[i][j] = sqrt(matrix.values[i][j]);
        }
    }

}
//=======================================================================================================
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
            values[i][j] = Cos(matrix.values[i][j]);
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
            values[i][j] = Tan(matrix.values[i][j]);
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
    //---------------------------------CotFunction----------------------------------------
void CMatrix::Csc(CMatrix& matrix)
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



