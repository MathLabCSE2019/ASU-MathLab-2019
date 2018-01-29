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
	bool b = false;
	for (int i = 1; i < s.length() - 1; i++) { if (s[i] != ' ' && s[i] != ';' && (s[i] < 48 || s[i] > 57)) { b = true; break; } }
	(b) ? mom(s) : copy(s);
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
	bool b = false;
	for (int i = 1; i < s.length() - 1; i++) { if (s[i] != ' ' && s[i] != ';' && (s[i] < 48 || s[i] > 57)) { b = true; break; } }
	(b) ? mom(s) : copy(s);
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





    /**_____________________________________________**/
    /**___________Matrix Power Operation____________**/
    /**_____________________________________________**/


CMatrix CMatrix::operator^(int x)
{
    //try
    //{
        CMatrix f;
        // x=-2;
        f=(*this).power(x);
        return f;
    //}
    /*catch(int i)
    {
        cout<<"Error:To get power of matrix,the matrix should have square dimensions";
    }*/

}

    //element element power//
CMatrix CMatrix::mpower(double x)
{
    CMatrix result_matrix(nR,nC);

    for(int i=0;i<nR;i++)
        for(int j=0;j<nC;j++)
        {
            if((values[i][j]==0)&&(x==0)) /** In Matlab : it's computed as 1 **/
                throw ("Error:0 can`t be raised to the power 0");

            result_matrix.values[i][j] = pow(values[i][j],x);
        }
     return result_matrix;
}

       //matrix power//

CMatrix CMatrix::power(int x)
{
    if(nR!=nC)throw 1;
    CMatrix result_matrix(nR , nC);
    for(int i=0;i<nR;i++)
        for(int j=0;j<nC;j++)
            result_matrix.values[i][j]=values[i][j];

    CMatrix temp;
    if(x<0)
    {
        result_matrix = result_matrix.getInverse();
        //result_matrix.getInverse(result_matrix);
        temp = result_matrix;
        x = x*-1;

        while(x>1)
        {
            result_matrix*=temp;
            x--;
        }
        return result_matrix;
    }
    else if(x==0)
    {
        CMatrix m = eye(nR,nC);
        return m;
    }
    else if(x>0)
    {
        while(x>1)
        {
            result_matrix*=(*this);
            x--;
        }
        return result_matrix;
    }
}



    /**________________________________________________**/
    /**_________ Matrix Logarithmic Operation__________**/
    /**________________________________________________**/



//log functions
//log10
CMatrix CMatrix::mlog10() //log function(log to the base 10)
{
    CMatrix output_matrix(nR , nC);
    for(int i=0;i<nR;i++)
        for(int j=0;j<nC;j++)
        {
            if( values[i][j]<1)
                throw 1;

            /*try
            {
                output_matrix.values[i][j]=log10(values[i][j]);
                return output_matrix;
            }
            catch(int z)
            {
                cout<<"Error: There is no log value for negative numbers"<<endl;
            }*/
            output_matrix.values[i][j]=log10(values[i][j]);
        }

     return output_matrix;
}


//log2

CMatrix CMatrix::mlog2() //log function(log to the base 2)
{
    CMatrix result_matrix(nR , nC);
    for(int i=0;i<nR;i++)
        for(int j=0;j<nC;j++)
        {
            if( values[i][j]<1)
                throw 1;

            /*try
            {
                result_matrix.values[i][j]=log2(values[i][j]);
                return result_matrix;
            }
            catch(int w)
            {
                cout<<"Error: There is no log value for negative numbers"<<endl;
            }*/

              result_matrix.values[i][j]=log2(values[i][j]);
        }

     return result_matrix;
}
//log
//natural log (ln function))
CMatrix CMatrix::mlog() //ln function
{
    CMatrix the_result_matrix(nR , nC);
    for(int i=0;i<nR;i++)
        for(int j=0;j<nC;j++)
        {
            if( values[i][j]<1)
                throw 1;

            /*try
            {
                the_result_matrix.values[i][j]=log(values[i][j]);
                return the_result_matrix;
            }
            catch(int v)
            {
                cout<<"Error: There is no log value for negative numbers"<<endl;
            }*/

            the_result_matrix.values[i][j]=log(values[i][j]);
        }

     return the_result_matrix;
}



    /**________________________________________________**/
    /**_________Matrix Trignometric Operation__________**/
    /**________________________________________________**/


//-----------------------------------SinFunction---------------------------------------
CMatrix Sin(CMatrix matrix)
{
    CMatrix result_matrix(matrix.nR,matrix.nC);
    for(int i=0 ; i<matrix.nR ; i++)
    {
        for(int j=0 ; j<matrix.nC ; j++)
        {
            result_matrix.values[i][j] = sin(matrix.values[i][j]);
        }
    }
    return result_matrix;
}

//-----------------------------------CosFunction---------------------------------------
CMatrix Cos(CMatrix matrix)
{
    CMatrix result_matrix(matrix.nR,matrix.nC);
    for(int i=0 ; i<matrix.nR ; i++)
    {
        for(int j=0 ; j<matrix.nC ; j++)
        {
            result_matrix.values[i][j] = cos(matrix.values[i][j]);
        }
    }
    return result_matrix;
}

//-----------------------------------TanFunction---------------------------------------
CMatrix Tan(CMatrix matrix)
{
    CMatrix result_matrix(matrix.nR,matrix.nC);
    for(int i=0 ; i<matrix.nR ; i++)
    {
        for(int j=0 ; j<matrix.nC ; j++)
        {
            result_matrix.values[i][j] = tan(matrix.values[i][j]);
        }
    }
    return result_matrix;
}

//---------------------------------CscFunction----------------------------------------
CMatrix Csc(CMatrix matrix)
{
    CMatrix result_matrix(matrix.nR,matrix.nC);
    for(int i=0 ; i<matrix.nR ; i++)
    {
        for(int j=0 ; j<matrix.nC ; j++)
        {
           result_matrix.values[i][j] = 1/sin(matrix.values[i][j]);
        }

    }
    return result_matrix;
}

//---------------------------------SecFunction----------------------------------------
CMatrix Sec(CMatrix matrix)
{
    CMatrix result_matrix(matrix.nR,matrix.nC);
    for(int i=0 ; i<matrix.nR ; i++)
    {
        for(int j=0 ; j<matrix.nC ; j++)
        {
           result_matrix.values[i][j] = 1/cos(matrix.values[i][j]);
        }
    }
    return result_matrix;
}

//---------------------------------CotFunction----------------------------------------
CMatrix Cot(CMatrix matrix)
{
    CMatrix result_matrix(matrix.nR,matrix.nC);
    for(int i=0 ; i<matrix.nR ; i++)
    {
        for(int j=0 ; j<matrix.nC ; j++)
        {
           result_matrix.values[i][j] = 1/tan(matrix.values[i][j]);
        }
    }
    return result_matrix;
}

//-----------------------------------------------SindFunction------------------------------------
CMatrix Sind(CMatrix matrix)
{
    CMatrix result_matrix(matrix.nR,matrix.nC);
    //float pi = 3.141592654;
    for(int i=0 ; i<matrix.nR ; i++)
    {
        for(int j=0 ; j<matrix.nC ; j++)
        {
           result_matrix.values[i][j] = sin((pi/180)*matrix.values[i][j]);
        }
    }
    return result_matrix;
}

//-----------------------------------------------CosdFunction---------------------------------
CMatrix Cosd(CMatrix matrix)
{
    CMatrix result_matrix(matrix.nR,matrix.nC);
    //float pi = 3.141592654;
    for(int i=0 ; i<matrix.nR ; i++)
    {
        for(int j=0 ; j<matrix.nC ; j++)
        {
            result_matrix.values[i][j] = cos((pi/180)*matrix.values[i][j]);
        }
    }
    return result_matrix;
}

//-----------------------------------------------TandFunction----------------------------------------------------
CMatrix Tand(CMatrix matrix)
{
    CMatrix result_matrix(matrix.nR,matrix.nC);
    //float pi = 3.141592654;
    for(int i=0 ; i<matrix.nR ; i++)
    {
        for(int j=0 ; j<matrix.nC ; j++)
        {
            result_matrix.values[i][j] = tan((pi/180)*matrix.values[i][j]);
        }
    }
    return result_matrix;
}

//-----------------------------------------------CscdFunction----------------------------------------------------
CMatrix Cscd(CMatrix matrix)
{
    CMatrix result_matrix(matrix.nR,matrix.nC);
    //float pi = 3.141592654;
    for(int i=0 ; i<matrix.nR ; i++)
    {
        for(int j=0 ; j<matrix.nC ; j++)
        {
            result_matrix.values[i][j] = 1/sin((pi/180)*matrix.values[i][j]);
        }
    }
    return result_matrix;
}

//-----------------------------------------------SecdFunction---------------------------------------------------
CMatrix Secd(CMatrix matrix)
{
    CMatrix result_matrix(matrix.nR,matrix.nC);
    //float pi = 3.141592654;
    for(int i=0 ; i<matrix.nR ; i++)
    {
        for(int j=0 ; j<matrix.nC ; j++)
        {
            result_matrix.values[i][j] = 1/cos((pi/180)*matrix.values[i][j]);
        }
    }
    return result_matrix;
}

//-----------------------------------------------CotdFunction----------------------------------------------------
CMatrix Cotd(CMatrix matrix)
{
    CMatrix result_matrix(matrix.nR,matrix.nC);
    //float pi = 3.141592654;
    for(int i=0 ; i<matrix.nR ; i++)
    {
        for(int j=0 ; j<matrix.nC ; j++)
        {
            result_matrix.values[i][j] = 1/tan((pi/180)*matrix.values[i][j]);
        }
    }
    return result_matrix;
}

//--------------------------------------------asinFunction------------------------------------------------------
CMatrix aSin(CMatrix matrix)
{
    CMatrix result_matrix(matrix.nR,matrix.nC);
    for(int i=0 ; i<matrix.nR ; i++)
    {
        for(int j=0 ; j<matrix.nC ; j++)
        {
            result_matrix.values[i][j] = asin(matrix.values[i][j]);
        }
    }
    return result_matrix;
}

//--------------------------------------------acosFunction------------------------------------------------------
CMatrix aCos(CMatrix matrix)
{
    CMatrix result_matrix(matrix.nR,matrix.nC);
    for(int i=0 ; i<matrix.nR ; i++)
    {
        for(int j=0 ; j<matrix.nC ; j++)
        {
            result_matrix.values[i][j] = acos(matrix.values[i][j]);
        }
    }
    return result_matrix;
}

//--------------------------------------------atanFunction------------------------------------------------------
CMatrix aTan(CMatrix matrix)
{
    CMatrix result_matrix(matrix.nR,matrix.nC);
    for(int i=0 ; i<matrix.nR ; i++)
    {
        for(int j=0 ; j<matrix.nC ; j++)
        {
            result_matrix.values[i][j] = atan(matrix.values[i][j]);
        }
    }
    return result_matrix;
}

//--------------------------------------------asecFunction------------------------------------------------------
CMatrix aSec(CMatrix matrix)
{
    CMatrix result_matrix(matrix.nR,matrix.nC);
    for(int i=0 ; i<matrix.nR ; i++)
    {
        for(int j=0 ; j<matrix.nC ; j++)
        {
            result_matrix.values[i][j] = acos(1/matrix.values[i][j]);
        }
    }
    return result_matrix;
}

//--------------------------------------------acscFunction------------------------------------------------------
CMatrix aCsc(CMatrix matrix)
{
    CMatrix result_matrix(matrix.nR,matrix.nC);
    for(int i=0 ; i<matrix.nR ; i++)
    {
        for(int j=0 ; j<matrix.nC ; j++)
        {
            result_matrix.values[i][j] = asin(1/matrix.values[i][j]);
        }
    }
    return result_matrix;
}

//--------------------------------------------acotFunction------------------------------------------------------
CMatrix aCot(CMatrix matrix)
{
    CMatrix result_matrix(matrix.nR,matrix.nC);
    for(int i=0 ; i<matrix.nR ; i++)
    {
        for(int j=0 ; j<matrix.nC ; j++)
        {
            result_matrix.values[i][j] = atan(1/matrix.values[i][j]);
        }
    }
    return result_matrix;
}



//-----------------------------------------SquareRootElementByElement---------------------------
/** friend function **/
 CMatrix squareRoot(CMatrix matrix)
{
    CMatrix result_matrix(matrix.nR , matrix.nC);
    for(int i=0;i<matrix.nR;i++)
    {
        for(int j=0;j<matrix.nC;j++)
        {
            result_matrix.values[i][j] = sqrt(matrix.values[i][j]);
        }
    }
    return result_matrix;
}
//=======================================================================================================
//=======================================SquareRootForAllMatrix================================================
/*
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
*/



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


void CMatrix::addMatrixHor(CMatrix& c)
{
	CMatrix m; m.nR = this->nR; m.nC = this->nC + c.nC;
	m.values = new double*[m.nR];
	for (int ir = 0; ir < nR; ir++)
	{
		m.values[ir] = new double[m.nC];
		for (int ic = 0; ic < m.nC; ic++)
		{
			m.values[ir][ic] = (ic < nC) ? values[ir][ic] : c.values[ir][ic - nC];
		}
	}
	copy(m);
}

void CMatrix::addMatrixVer(CMatrix& c)
{
	CMatrix m; m.nR = this->nR + c.nR; m.nC = this->nC;
	m.values = new double*[m.nR];
	for (int ir = 0; ir < m.nR; ir++)
	{
		m.values[ir] = new double[m.nC];
		for (int ic = 0; ic < m.nC; ic++)
		{
			m.values[ir][ic] = (ir < nR) ? values[ir][ic] : c.values[ir - nR][ic];
		}
	}
	copy(m);
}
void CMatrix::mom(string s)
{
	string str = s; int i = 0;
	str.erase(0, 1); str.erase(str.length() - 1, str.length());
	CMatrix m;
	while (str[0] == ' ') str.erase(0, 1);
	if (str[0] > 47 && str[0] < 58 || str[0] == '.' || str[0] == '-')
	{
		string fe = str.substr(0, (str.find(" ") < str.find(";")) ? str.find(" ") : str.find(";"));
		double d = strtod(fe.c_str(), NULL);
		m = d;
		str.erase(0, fe.length());
	}
	else if (str[0] == '[')
	{
		string fe = str.substr(0, str.find("]") + 1);
		m = fe;
		str.erase(0, fe.length());
	}
	//else -> letter cases here
	while (str.length())
	{
		if (str[0] == ' '){ if (!i) i = 1; str.erase(0, 1); }
		else if (str[0] == ';' || str[0] == '\n') { i = 2; str.erase(0, 1); }
		else if (str[0] > 47 && str[0] < 58 || str[0] == '.' || str[0] == '-')
		{
			string fe = str.substr(0, (str.find(" ") < str.find(";")) ? str.find(" ") : str.find(";"));
			double d = strtod(fe.c_str(), NULL);
			CMatrix cm = d;
			(i == 1) ? m.addMatrixHor(cm) : m.addMatrixVer(cm);
			str.erase(0, fe.length());
			i = 0;
		}
		else if (str[0] == '[')
		{
			string fe = str.substr(0, str.find("]") + 1);
			CMatrix cm = fe;
			(i == 1) ? m.addMatrixHor(cm) : m.addMatrixVer(cm);
			str.erase(0, fe.length());
			i = 0;
		}
	}
	*this = m;
}