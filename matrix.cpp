#include "matrix.h"

using namespace std;


    /**_____________________________________________**/
    /**____________ Matrix Constructors_____________**/
    /**_____________________________________________**/


CMatrix::CMatrix()
{
	nR = nC = 0;
	values = NULL;
}

CMatrix::~CMatrix()
{
	reset();
}

CMatrix::CMatrix(int nR, int nC, int initialization, double initializationValue)
{
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

CMatrix::CMatrix(int nR, int nC, double first, ...)
{
	this->nR = nR;
	this->nC = nC;
	if ((nR*nC) == 0){
		values = NULL;
		return;
	}
	values = new double*[nR];
	va_list va;
	va_start(va, first);
	for (int iR = 0; iR<nR; iR++)
    {
        values[iR] = new double[nC];
        for (int iC = 0; iC<nC; iC++)
        {
            values[iR][iC] = (iC == 0 && iR == 0) ? first : va_arg(va, double);
        }
	}
	va_end(va);
}


CMatrix::CMatrix(const CMatrix& m)
{
	nR = nC = 0;
	values = NULL;
	copy(m);
}

CMatrix::CMatrix(double d)
{
	nR = nC = 0;
	values = NULL;
	copy(d);
}

CMatrix::CMatrix(string s)
{
	nR = nC = 0;
	values = NULL;
	copy(s);
}



    /**_____________________________________________**/
    /**_________Matrix Equality Operations__________**/
    /**_____________________________________________**/


CMatrix CMatrix::operator=(const CMatrix& m)
{
	copy(m);
	return *this;
}


CMatrix& CMatrix::operator=(double d)
{
	copy(d);
	return *this;
}


CMatrix CMatrix::operator=(string s)
{
    copy(s);
    return *this;
}

void CMatrix::copy(const CMatrix& m)
{
	reset();
	this->nR = m.nR;
	this->nC = m.nC;
	if ((nR*nC) == 0){
		values = NULL;
		return;
	}
	values = new double*[nR];
	for (int iR = 0; iR<nR; iR++)
    {
		values[iR] = new double[nC];
		for (int iC = 0; iC<nC; iC++){ values[iR][iC] = m.values[iR][iC]; }
	}
}

void CMatrix::copy(double d)
{
	reset();
	this->nR = 1;
	this->nC = 1;
	values = new double*[1];
	values[0] = new double[1];
	values[0][0] = d;
}

void CMatrix::copy(string s)
{
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



    /**_____________________________________________**/
    /**________ Matrix Addition Operation___________**/
    /**_____________________________________________**/

void CMatrix::add(CMatrix m)
{
	if (nR != m.nR || nC != m.nC)throw("Invalid matrix dimension");
	for (int iR = 0; iR<nR; iR++)for (int iC = 0; iC<nC; iC++)values[iR][iC] += m.values[iR][iC];
}


void CMatrix::operator+=(CMatrix m)
{
    add(m);
}


void CMatrix::operator+=(double d)
{
	CMatrix a(nR, nC, MI_VALUE, d);
	add(a);
}


CMatrix CMatrix::operator+(CMatrix m)
{
	CMatrix r = *this;
	r += m;
	return r;
}

CMatrix CMatrix::operator+(double d)
{
    CMatrix r = *this;
    r += d;
    return r;
}


    /**_____________________________________________**/
    /**________ Matrix Subtraction Operation________**/
    /**_____________________________________________**/



void CMatrix::sub(CMatrix m)
{
	if (nR != m.nR || nC != m.nC)throw("Invalid matrix dimension");
	for (int iR = 0; iR<nR; iR++)for (int iC = 0; iC<nC; iC++)values[iR][iC] -= m.values[iR][iC];
}

void CMatrix::operator-=(CMatrix m)
{
    sub(m);
}

void CMatrix::operator-=(double d)
{
	CMatrix h(nR, nC, MI_VALUE, d);
	sub(h);
}

CMatrix CMatrix::operator-(CMatrix m)
{
	CMatrix r = *this;
	r -= m;
	return r;
}

CMatrix CMatrix::operator-(double d)
{
    CMatrix r = *this;
    r -= d;
    return r;
}


    /**________________________________________________**/
    /**________ Matrix Multiplication Operation________**/
    /**________________________________________________**/


void CMatrix::mul(CMatrix m)
{
	if (nR != m.nR || nC != m.nC)throw("Invalid matrix dimension");
	CMatrix r(nR, m.nC);
	for (int iR = 0; iR<r.nR; iR++)for (int iC = 0; iC<r.nC; iC++)
    {
		r.values[iR][iC] = 0;
		for (int k = 0; k<m.nC; k++)r.values[iR][iC] += values[iR][k] * m.values[k][iC];
	}
	copy(r);
}

void CMatrix::operator*=(CMatrix m)
{
    mul(m);
}

void CMatrix::operator*=(double d)
{
	for (int iR = 0; iR<nR; iR++)for (int iC = 0; iC<nC; iC++)values[iR][iC] *= d;
}

CMatrix CMatrix::operator*(CMatrix m)
{
    CMatrix r = *this;
    r *= m;
    return r;
}

CMatrix CMatrix::operator*(double d)
{
    CMatrix r = *this;
    r *= d;
    return r;
}

/** c = a.element_mul(b); **/
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




    /**_____________________________________________**/
    /**__________Matrix Division Operation__________**/
    /**_____________________________________________**/



void CMatrix::operator/=(CMatrix another_matrix)
{
    if(nR != another_matrix.nR || nC != another_matrix.nC)
        throw("Invalid Matrix Dimention");

    *this = *this / another_matrix;
}

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


CMatrix CMatrix:: operator/(CMatrix another_matrix)
{
    if(nR != another_matrix.nR || nC != another_matrix.nC)
        throw("Invalid Matrix Dimention");

    CMatrix result_matrix = *this;
    another_matrix = another_matrix.getInverse();
    result_matrix = result_matrix * another_matrix;

    return result_matrix;
}


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



    /**_____________________________________________**/
    /**______________Matrix Increment_______________**/
    /**_____________________________________________**/


CMatrix CMatrix::operator++()
{
	CMatrix s(nR, nC, MI_VALUE, 1.0);
	add(s);
	return *this;
}

CMatrix CMatrix::operator++(int)
{
	CMatrix C = *this;
	CMatrix f(nR, nC, MI_VALUE, 1.0);
	add(f);
	return C;
}

CMatrix CMatrix::operator--()
{
	CMatrix v(nR, nC, MI_VALUE, -1.0); add(v);
	return *this;
}

CMatrix CMatrix::operator--(int)
{
	CMatrix r = *this;
	CMatrix n(nR, nC, MI_VALUE, -1.0); add(n);
	return r;
}



/** signed matrix **/


CMatrix CMatrix::operator-()
{
	for (int iR = 0; iR<nR; iR++)for (int iC = 0; iC<nC; iC++)values[iR][iC] = -values[iR][iC]; return *this;
}

CMatrix CMatrix::operator+()
{
    return *this;
}



    /**_____________________________________________**/
    /**_____________Matrix I/O Stream ______________**/
    /**_____________________________________________**/


istream& operator >> (istream &is, CMatrix& m)
{
	string s;
	CMatrix n(s);
	getline(is, s, ']');
	s += "]";
	// not sure here **
	m.copy(n);
	return is;
}

ostream& operator << (ostream &os, CMatrix& m)
{
	os << m.getString();
	return os;
}




    /**_____________________________________________**/
    /**_____________Matrix Manipulation_____________**/
    /**_____________________________________________**/


void CMatrix::print()
{
	for (int iR = 0; iR < nR; iR++)
        for (int iC = 0; iC < nC; iC++)
            cout << values[iR][iC]<<endl;
}

void CMatrix::reset()
{
	if (values)
    {
		for (int i = 0; i<nR; i++)delete[] values[i];
		delete[] values;
	}
	nR = nC = 0;
	values = NULL;
}

string CMatrix::getString()
{
	string s;
	for (int iR = 0; iR<nR; iR++)
	{
		for (int iC = 0; iC<nC; iC++)
        {
			char buffer[20];
			//snprintf(buffer, 10, "%g\t\t", values[iR][iC]);
			sprintf(buffer ,"%# .5lf\t" , values[iR][iC]);
			s += buffer;
		}
		s += "\n";
	}
	return s;
}

void CMatrix::setSubMatrix(int r, int c, CMatrix& m)
{
	if ((r + m.nR)>nR || (c + m.nC)>nC)throw("Invalid matrix dimension");
	for (int iR = 0; iR<m.nR; iR++)
        for (int iC = 0; iC<m.nC; iC++)
            values[r + iR][c + iC] = m.values[iR][iC];
}

CMatrix CMatrix::getSubMatrix(int r, int c, int nr, int nc)
{
	if ((r + nr)>nR || (c + nc)>nC)throw("Invalid matrix dimension");
	CMatrix m(nr, nc);
	for (int iR = 0; iR<m.nR; iR++)
        for (int iC = 0; iC<m.nC; iC++)
            m.values[iR][iC] = values[r + iR][c + iC];
    return m;
}

void CMatrix::addColumn(CMatrix& m)
{
	CMatrix n(max(nR, m.nR), nC + m.nC);
	//errorrrr
	//n.setMatrix(0, 0, *this);
	//n.setMatrix(0, nC, m); *this = n;
}

void CMatrix::addRow(CMatrix& m)
{
	CMatrix n(nR + m.nR, max(nC, m.nC));
	//errrorr
	//n.setMatrix(0, 0, *this);
	//n.setMatrix(nR, 0, m); *this = n;
}

CMatrix CMatrix::getCofactor(int r, int c)
{
	if (nR <= 1 && nC <= 1)throw("Invalid matrix dimension");
	CMatrix m(nR - 1, nC - 1);
	for (int iR = 0; iR<m.nR; iR++)
        for (int iC = 0; iC<m.nC; iC++)
        {
            int sR = (iR<r) ? iR : iR + 1;
            int sC = (iC<c) ? iC : iC + 1;
            m.values[iR][iC] = values[sR][sC];
        }
	return m;
}



    /**_____________________________________________**/
    /**__________Matrix Advanced Operation__________**/
    /**_____________________________________________**/


double CMatrix::getDeterminant()
{
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


CMatrix CMatrix:: getTranspose()
{
    CMatrix another_matrix = *this;
    for(int r = 0 ; r < nR ; r++)
    {
        for(int c = 0 ; c < nC ; c++)
        {
            another_matrix.values[r][c] = this->values[c][r];
        }
    }
    return another_matrix;
}


CMatrix CMatrix:: getInverse()
{
    CMatrix another_matrix = *this;

    double det =  another_matrix.getDeterminant(); //this->getDeterminant();
    if(!det) {cout<<"Invalid Matrix Operation";}
    else
    {
        double sign_correction = 1;
        for(int i = 0 ; i < nR ; i++)
        {
            for(int j = 0 ; j < nC ; j++)
            {
                another_matrix.values[i][j] = sign_correction * this->getCofactor(i,j).getDeterminant();
                sign_correction *= -1;
            }
        }
        another_matrix /= det;
        another_matrix = another_matrix.getTranspose();
    }

    int  sign_correction = 1;
    for(int i = 0 ; i < nR ; i++)
    {
        for(int j = 0 ; j < nC ; j++)
        {
            another_matrix.values[i][j] *= sign_correction;
            sign_correction *= -1;
        }
    }

    return another_matrix;
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


/**=================================================================**/

    /**_____________________________________________**/
    /**___________Matrix Outer Operation____________**/
    /**_____________________________________________**/


CMatrix mrand(int R , int C)
{
    if(C == 0)
    {
        CMatrix result_matrix(R , R , MI_RAND);
        return result_matrix;
    }
    else if(R == 0 && C != 0)
    {
        throw("Invalid");
    }
    else
    {
       CMatrix result_matrix(R , C , MI_RAND);
       return result_matrix;
    }
}

CMatrix eye(int R , int C)
{
    if(C == 0)
    {
        CMatrix result_matrix(R , R , MI_EYE);
        return result_matrix;
    }
    else
    {
        CMatrix result_matrix(R , C , MI_EYE);
        return result_matrix;
    }
}

CMatrix zeros(int R , int C)
{
    if(C == 0)
    {
        CMatrix result_matrix(R , R , MI_ZEROS);
        return result_matrix;
    }
    else
    {
        CMatrix result_matrix(R , C , MI_ZEROS);
        return result_matrix;
    }
}

CMatrix ones(int R , int C)
{
    if(C == 0)
    {
        CMatrix result_matrix(R , R , MI_ONES);
        return result_matrix;
    }
    else
    {
        CMatrix result_matrix(R , C , MI_ONES);
        return result_matrix;
    }
}
