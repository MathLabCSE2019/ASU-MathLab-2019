#include <iostream>
#include "Matrix.h"
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

//----------------------------------------
int pos_search(vector <string> x, string c){ //will need it to know where a var exists already
int pos = 0;
for(int i=0;i<x.size();i++){
    for(int j=0;j<x[i].length();j++){
        if(x[i].substr(j,1)==" ")x[i].erase(i,1);
    }
    for(int j=0;j<c.length();j++){
        if(c.substr(j,1)==" ")c.erase(i,1);
    }
    if( x[i].substr(0,1) == c.substr(0,1)){
        pos = i;
    }
}
return pos;
}


bool char_exist(string x, string y){ //Will need to know if certain char exist in string
bool exist = false;
int siz = x.size();
int i =0;
for(i=0;i<siz;i++){
    if(x.substr(i,1)=="."){
        if(x.substr(i,2)==y){
            exist =true;
            i++;
        }
     }
    else if(x.substr(i,1)==y){
        exist = true;
    }
}
return exist;
}
bool string_exist_3letter(string x, string y){ //Will need to know if certain string exist in string
bool exist = false;
int siz = x.size();
int i =0;
for(i=0;i<siz;i++){
 if(x.substr(i,1)==y.substr(i,1)){
        if(x.substr(i+1,1)==y.substr(i+1,1)){
                if(x.substr(i+2,1)==y.substr(i+2,1)){exist = true;}}
    }
}
return exist;
}
bool isThereChars(string s){
if(char_exist(s,"A")||char_exist(s,"B")||char_exist(s,"C")||char_exist(s,"D")||char_exist(s,"E")||char_exist(s,"F")||char_exist(s,"G")||char_exist(s,"H")||char_exist(s,"I"))return true;
if(char_exist(s,"J")||char_exist(s,"K")||char_exist(s,"L")||char_exist(s,"M")||char_exist(s,"N")||char_exist(s,"O")||char_exist(s,"P")||char_exist(s,"Q")||char_exist(s,"R"))return true;
if(char_exist(s,"S")||char_exist(s,"T")||char_exist(s,"U")||char_exist(s,"V")||char_exist(s,"W")||char_exist(s,"X")||char_exist(s,"Y")||char_exist(s,"Z"))return true;
else return false;
}
bool isTherechars(string s){
if(char_exist(s,"a")||char_exist(s,"b")||char_exist(s,"c")||char_exist(s,"d")||char_exist(s,"e")||char_exist(s,"f")||char_exist(s,"g")||char_exist(s,"h")||char_exist(s,"i"))return true;
if(char_exist(s,"j")||char_exist(s,"k")||char_exist(s,"l")||char_exist(s,"m")||char_exist(s,"n")||char_exist(s,"o")||char_exist(s,"p")||char_exist(s,"q")||char_exist(s,"r"))return true;
if(char_exist(s,"s")||char_exist(s,"t")||char_exist(s,"u")||char_exist(s,"v")||char_exist(s,"w")||char_exist(s,"x")||char_exist(s,"y")||char_exist(s,"z"))return true;
else return false;
}

string operation(string x){
string y = "";
if(char_exist(x,"+")){
    y +="+";
}
else if(char_exist(x,"-")){
    y +="-";
}
else if(char_exist(x,"./")){
    y +="./";
}
else if(char_exist(x,".*")){
    y +=".*";
}
else if(char_exist(x,"*")){
    y +="*";
}
else if(char_exist(x,"/")){
    y +="/";
}
else if(char_exist(x,"\'")){
    y +="\'";
}
return y;
}
bool operationExist(string x){
bool y = false;
if(char_exist(x,"+")){
    y = true;
}
 if(char_exist(x,"-")){
   y = true;
}
 if(char_exist(x,"./")){
    y = true;
}
 if(char_exist(x,".*")){
    y = true;
}
 if(char_exist(x,"*")){
    y = true;
}
 if(char_exist(x,"/")){
     y = true;
}
 if(char_exist(x,"\'")){
     y = true;
}
 if(char_exist(x,"^")){
     y = true;
}
 if(char_exist(x,".+")){
     y = true;
}
 if(char_exist(x,".-")){
     y = true;
}
 if(char_exist(x,".^")){
     y = true;
}
 return y;
}

bool exist(vector <string> x, string c){ //will need it to know if a var exists or not
    int rexist = 0;
    for(int i=0; i<x.size();i++){
        if(c == x[i]){
            rexist = 1;
        }
    }
  return rexist;
}

string varChar (string x){ //find var before '=' sign
        istringstream readInput(x);
        string varTemp = "";
        getline(readInput, varTemp,'=');
        for(int i=0; i<varTemp.length(); i++){
            if(varTemp[i] == ' ') varTemp.erase(i,1);
        }
        if(!char_exist(x,"="))return x.substr(0,1);
        return varTemp;
}

string aVarChar (string x, bool bfOp){ //to find vars to do operations on bfOp true to find before operation false to find after
        x=x.substr(x.find_first_of('=')+1);
        istringstream readInput(x);
        string varTemp = "";
        string op = operation(x);
        if(bfOp){
        getline(readInput, varTemp,op[0]);
        for(int i=0; i<varTemp.length(); i++){
            if(varTemp[i] == ' ') varTemp.erase(i,1);
            if(varTemp[i] == '.') varTemp.erase(i,1);
            if(varTemp[i] == '/') varTemp.erase(i,1);
            if(varTemp[i] == '*') varTemp.erase(i,1);
        }
        }
        else{
            varTemp = x.substr(x.find_first_of(op)+1,x.length()-x.find_first_of(op)+1);
            for(int i=0; i<varTemp.length(); i++){
                if(varTemp[i] == ' ') varTemp.erase(i,1);
                if(varTemp[i] == ';') varTemp.erase(i,1);
                if(varTemp[i] == '.') varTemp.erase(i,1);

            }
        }

        return varTemp;
}


int char_pos(string x,char c){ /** pos is edited from NULLL to 0 **/
int pos = NULL;
for(int i=0;i<x.length();i++){
    if(x[i]==c){
        pos =i;
        }

    }
return pos;
}

void opCalc(CMatrix a, CMatrix b, CMatrix& c, string o){
       if(o == "+"){
        c = a + b;
        cout<<endl<<c<<endl;
       }
       else if(o == "-"){
        a.sub(b);
        c=a;
        cout<<endl<<c<<endl;
       }
       else if(o == "*"){
        a.mul(b);
        c=a;
        cout<<endl<<c<<endl;
       }
        else if(o == "./"){
       c =  a.element_div(b);
        cout<<endl<<c<<endl;
       }
       else if(o == "/"){
        c=a/b;
        cout<<endl<<c<<endl;
       }
       else if(o==".*"){
        c =  a.element_mul(b);
        cout<<endl<<c<<endl;
       }
       else if(o == "\'"){
        c=a;
        c.getTranspose();
        cout<<endl<<c<<endl;
       }
}
void opCalc(double a, CMatrix b, CMatrix& c,string o){
       if(o == "+"){
        b+=a;
        c = b;
        cout<<endl<<c<<endl;
       }
       else if(o == "-"){
        b*=-1;
        b+=a;
        c = b;
        cout<<endl<<c<<endl;
       }
       else if(o == "*"){
        b*=a;
        c =b;
        cout<<endl<<c<<endl;
       }
       else if(o == "/"){
        c = b.element_div(a);
        cout<<endl<<c<<endl;
       }
       else if(o == "./"){
        c = b.element_div(a);
        cout<<endl<<c<<endl;
       }
       else if(o== ".*"){
        b*=a;
        c = b;
        cout<<endl<<c<<endl;
       }
       }

void opCalc(CMatrix a, double b, CMatrix& c,string o){
       if(o == "+"){
        c= a + b;
        cout<<endl<<c<<endl;
       }
       else if(o == "-"){
        c= a - b;
        cout<<endl<<c<<endl;
       }
       else if(o == "*"){
        a*=b;
        c=a;
        cout<<endl<<c<<endl;
       }
       else if(o == "/"){
       c= a / b;
        cout<<endl<<c<<endl;
       }
       else if(o == "./"){
        c= a / b;
        cout<<endl<<c<<endl;
       }
       else if(o== ".*"){
        a*=b;
        c = a;
        cout<<endl<<c<<endl;
       }
}

bool numExist(string x){
    bool res=false;
    if(char_exist(x,"1")||char_exist(x,"2")||char_exist(x,"3")||char_exist(x,"4")||char_exist(x,"5")||char_exist(x,"6")||char_exist(x,"7")||char_exist(x,"8")||char_exist(x,"9")||char_exist(x,"0")){
        res =true;
    }
    return res;
}
int countChar(string s , char c){ //count number of specific char in string
int counter = 0;
for(int i=0; i<s.length(); i++){
    if(s[i] == c)counter++;
}
return counter;
}

string cleanString (string x) { for(int i =0;i<x.size();i++){ if(x.substr(i,1)==x.substr(i+1,1)&&x.substr(i,1)==" ") {x. erase(i,1) ; i--;} } return x; }
string cleanAllSpace(string x){ for(int i =0; i<x.size(); i++){ if(x.substr(i,1)==" "){x.erase(i,1);}} return x;}
int nColumn(string s){
}

int nRow(string s , int line , int Braket){
    int nR = 0 ,nRin = 0;
int subMatrixPos[Braket*2];
subMatrixPos[0]= s.find('[');
subMatrixPos[1]= s.find_last_of(']');
cout<<subMatrixPos[0]<<" "<<subMatrixPos[1]<<endl;
for(int i = 2;i<Braket*2;i+=2){
    subMatrixPos[i] = s.find('[',subMatrixPos[i-2]+1);
    subMatrixPos[i+1] = s.find(']',subMatrixPos[i]+1);
    cout<<subMatrixPos[i]<<" "<<subMatrixPos[i+1]<<endl;
}
for(int i =0; i<s.size();i++){
if(s[i]==';'){
        int flage =0;
    for(int k =2;k<Braket;k+=2){
        if(i>subMatrixPos[k]&&i<subMatrixPos[k+1]){nRin++;
        flage = 1;}
    }
if(!flage)nR++;
}
}
cout<<nR<<"=="<<line<<"=="<<nRin<<endl;
return (nR + line + nRin);
}
int  charsExistInString(string s,vector <string> &x,int &n , vector <string> vars , vector <CMatrix> varValues){
    int type = 0 ,m;
    int equality = s.find("=");
    s = s.substr(equality+1);
  if(char_exist(s,"A")){x.push_back("A");n++;if(exist(vars,"A")){int i = pos_search(vars,"A");if(varValues[i].getnC()==1&&varValues[i].getnR()==1)return 1;}else{cout<<"There is undefined variable"<<endl;return;}}
  if(char_exist(s,"B")){x.push_back("B");n++;}
   if(char_exist(s,"C")){x.push_back("C");n++;}
   if(char_exist(s,"D")){x.push_back("D");n++;}
   if(char_exist(s,"E")){x.push_back("E");n++;}
   if(char_exist(s,"F")){x.push_back("F");n++;}
   if(char_exist(s,"G")){x.push_back("G");n++;}
   if(char_exist(s,"H")){x.push_back("H");n++;}
   if(char_exist(s,"I")){x.push_back("I");n++;}
   if(char_exist(s,"J")){x.push_back("J");n++;}
   if(char_exist(s,"K")){x.push_back("K");n++;}
   if(char_exist(s,"L")){x.push_back("L");n++;}
   if(char_exist(s,"M")){x.push_back("M");n++;}
   if(char_exist(s,"N")){x.push_back("N");n++;}
   if(char_exist(s,"O")){x.push_back("O");n++;}
   if(char_exist(s,"P")){x.push_back("P");n++;}
   if(char_exist(s,"Q")){x.push_back("Q");n++;}
   if(char_exist(s,"R")){x.push_back("R");n++;}
   if(char_exist(s,"S")){x.push_back("S");n++;}
   if(char_exist(s,"T")){x.push_back("T");n++;}
   if(char_exist(s,"U")){x.push_back("U");n++;}
   if(char_exist(s,"V")){x.push_back("V");n++;}
   if(char_exist(s,"W")){x.push_back("W");n++;}
   if(char_exist(s,"X")){x.push_back("X");n++;}
   if(char_exist(s,"Y")){x.push_back("Y");n++;}
   if(char_exist(s,"Z")){x.push_back("Z");n++;}
   return 5;
}
double checkForArithmatic(string aa){
double b;
int posSin = aa.find("sin");
int posCos = aa.find("cos");
int posLog = aa.find("log");
int posSqrt = aa.find("sqrt");
int posExp = aa.find("exp");
//cout<<aa<<"~~~~~~~~~~~~~~~~~~~~~~~"<<posSin<<endl;
if(posSin>=0){aa = aa.substr(posSin+3);b=sin(stof(aa));}
  //  else if (posCos>0){aa = aa.substr(aa.find('(')+1,aa.find(')')-aa.find('(')-1);b=cos(stof(aa));}
    //else if(posLog>0){aa = aa.substr(aa.find('(')+1,aa.find(')')-aa.find('(')-1);b=log(stof(aa));}
    //else if(posSqrt>0){aa = aa.substr(aa.find('(')+1,aa.find(')')-aa.find('(')-1);b=sqrt(stof(aa));}
    else {b = stof(aa);}
    //b = stof(aa);
   // cout<<b<<endl;
    //cout<<"%%%aa"<<" "<<aa<<endl;
    return b;
}
string pairOperation(string s , string operation ,int &Beg , int &End){ //operation between two double
double opResult =0;
double a;
string aa;
double b;
int negFix = 0;
if(s.substr(0,1)=="-")negFix++;
int op = s.find(operation,negFix);
for(int i =op+1;i<s.size();i++){
    if(operationExist(s.substr(i,1))){
        aa = s.substr(op+1,i-op-1);
        if(s.substr(op,1)=="-"){aa = s.substr(op,i-op);}
        //    cout<<"%%%%1 "<<aa<<endl;
        b = checkForArithmatic(aa);
            End = i-1;
             break;}
    else if(i==s.size()-1){
        aa = s.substr(op+1);
       //  cout<<"%%%%2 "<<aa<<endl;
        b = checkForArithmatic(aa);
         End = s.size()-1;
         break;
    }
}
for(int i =op-1;i<s.size();i--){
    if(operationExist(s.substr(i,1))){
            aa = s.substr(i+1,op-i-1);
            Beg = i+1;
            if(s.substr(i,1)=="-"){
                    aa = s.substr(i,op-i);
                    Beg =i;
                    }
           //  cout<<"%%%%3 "<<aa<<endl;
            a = checkForArithmatic(aa);
             break;}
    else if(i==0){
         aa = s.substr(i,op-i);
        //  cout<<"%%%%4 "<<aa<<endl;
        a = checkForArithmatic(aa);
        Beg = 0;
         break;
    }

}
//cout<<s<<"  BBBBBBBeg: "<<Beg<<"Ennnd: "<<End<<endl;
//cout<<"a: "<<a<<" b: "<<b<<endl;
if(operation=="+")opResult = a + b;
else if(operation=="-")opResult = a - b;
else if(operation=="*")opResult = a*b;
else if(operation=="/"){if(b!=0)opResult = a/b;else {cout<<"Undefined Operation"<<endl;opResult=0;}}
else if(operation=="^")opResult=pow(a,b);
//cout<<"a: "<<a<<" b: "<<b<<" op: "<<operation<<" result: "<<opResult<<endl;

ostringstream ss;
ss<<opResult;
//cout<<"***********str: "<<ss.str()<<endl;
return ss.str();
}
double stringOperation(string s){ //return calculation for line of operation
 double opResult =0;
string a;
int from , to;
//cout <<"************ a : "<<s<<"from to"<<from<<" " <<to<<endl;
while(char_exist(s,"^")){
a = pairOperation(s,"^",from,to);
//cout<<"aaaaaaaaaa: "<<s<<endl;
s.replace(from,to-from+1,a);
//cout<<"sssssssss: "<<s<<"size:"<<s.size()<<" "<<from<<" "<<to<<endl;
//cout<<"sssssssss: "<<s<<endl;
}
while(char_exist(s,"*")){
a = pairOperation(s,"*",from,to);
//cout<<"aaaaaaaaaa: "<<s<<endl;
s.replace(from,to-from+1,a);
//cout<<"sssssssss: "<<s<<"size:"<<s.size()<<" "<<from<<" "<<to<<endl;
//cout<<"sssssssss: "<<s<<endl;
}
while(char_exist(s,"/")){
a = pairOperation(s,"/",from,to);
//cout<<"aaaaaaaaaa: "<<s<<endl;
s.replace(from,to-from+1,a);
/*for(int i =0;i<s.size();i++){
if(s.substr(i,1)==s.substr(i+1,1)&&s.substr(i,1)=="-")s.erase(i);
}*/
//cout<<"sssssssss: "<<s<<" "<<from<<" "<<to<<endl;
//cout<<"sssssssss: "<<s<<endl;
}
while(char_exist(s,"+")){
a = pairOperation(s,"+",from,to);
//cout<<"aaaaaaaaaa: "<<a<<endl;
s.replace(from,to-from+1,a);
/*for(int i =0;i<s.size();i++){
if(s.substr(i,1)==s.substr(i+1,1)&&s.substr(i,1)=="-")s.erase(i);
}*/
//cout<<"sssssssss: "<<s<<"size:"<<s.size()<<" "<<from<<" "<<to<<endl;
//cout<<"sssssssss: "<<s<<endl;
}
while(char_exist(s,"-")){
//cout<<"########"<<s<<endl;
a = pairOperation(s,"-",from,to);
//cout<<"aaaaaaaaaa: "<<a<<endl;
s.replace(from,to-from+1,a);
//cout<<"sssssssss: "<<s<<" "<<from<<" "<<to<<endl;
//cout<<"sssssssss: "<<s<<endl;
if(s.find("-") == 0 && !operationExist(s.substr(1))){break;}
}
opResult = stof(s);
//cout<<"============== "<<opResult<<endl;
return opResult;
}

double oneToOneOperationCalculation(string s){ //operation for matrix 1*1
    double result = 0;
    s = s.substr(s.find("=")+1);
    s = cleanAllSpace(s);
  int braket = s.find("(");
 if(braket<0 && braket<1000){
    // cout<<"@@@@"<<endl;
    result = stringOperation(s);
 }else{
 int endBraket = s.find(")",braket);
 int k=0;
while(endBraket>0){
for(int i=1;i<100;i++){
if(s.find("(",braket+i)<endBraket){
        braket = s.find("(",braket+i);
        k++;
}else break;
}
string opString = s.substr(braket+1,endBraket-braket-1);
if(operationExist(opString)){
result = stringOperation(opString);
}else{
result = stof(opString);
}
ostringstream ss;
ss<<result;
s = s.replace(braket,endBraket-braket+1,ss.str());
    //cout<<"in "<<s<<endl;
   // cout<<"inn "<<opString<<" result: "<<result<<endl;
   // cout<<braket<<" "<<endBraket<<endl;
  endBraket = s.find(")",endBraket+1);
  if(endBraket<0 && k>0){
       // cout<<"whattttttttttttttttttt"<<endl;
  braket = s.find("(");
  endBraket = s.find(")",braket);
  k--;
  }
}
if(operationExist(s)){
     //  cout<<"#";
     result = stringOperation(s);
if(s.find("-") == 0 && operationExist(s.substr(1))){
   // cout<<" ##";
result = stringOperation(s);}
}}
//cout<<"$$$ "<<result<<endl;
return result;
}

int main (int argc, char* argv[]){
    //---------------------input---------------------------------------------------------------------
vector <string> vars;
CMatrix varValues[1000];
int nV = 0 ;
int varExists = 0;
    string input[10] = ""; //for multi-line input
    int nLine = 1; // number of line in any input
    //-------------------read input from file--------------------------------------------------------
ifstream in ("advexample.m");
if(in.is_open()){
    while( !in.eof() ){
    if(!varExists)getline(in,input[0]);
    cout<<"Input: "<<input[0]<<endl;
    input[0] = cleanString(input[0]);
    int semicolon = input[0].find(";");
if(semicolon>0)input[0].erase(semicolon,1);
   // cout<<input[0]<<endl;
    string tvar = varChar(input[0]);
    if(!exist(vars,tvar)){ //------------ var not exist -----------------//
        if(char_exist(input[0],"=")){ //for multi-line
                vars.push_back(tvar);
         //       cout<<"**"<<tvar<<endl;
         }
    int inputBegNum = countChar(input[0],'[');
    int inputEndNum = countChar(input[0],']');
    if((inputBegNum>0||inputEndNum>0)&&(inputBegNum == inputEndNum)&&(nLine == 1)){ //check for one line input
      nLine = 1;
      //cout<<"one line input!"<<endl;
    }else if(inputBegNum>0||inputEndNum>0){ //check for multi-line input
      //cout<<"multi-line input!"<<endl;
       if(nLine==1){input[1] = input[0];
       nLine = 2;}
       else{
       cout<<"this is the full line"<<endl<<input[1]<<endl<<input[0]<<endl;
        nLine = 1;nV--;}}
   else if(char_exist(input[0],"=")){ // this is operation ------------------------------------------
   //cout<<"operation!"<<endl;
   vector <string> varsInOperation;
   int n = 0;
int type = charsExistInString(input[0],varsInOperation,n,vars,varValues); // know all matrix variables in the operation
if(type == 1 && operationExist(input[0])){ // return 1*1 matrix
int a = countChar(input[0],'(');
int b = countChar(input[0],')');
if(a != b){
    cout<<"Invalid Input!"<<endl;
    //----------------------------------------------------------------------------------------------
}
else{
if(varsInOperation.)        
varValues[nV] = oneToOneOperationCalculation(input[0]);
cout <<vars[nV]<<" = "<<endl<<varValues[nV]<<endl;}
}
else if (n==0 && isTherechars(input[0])){ // return MI Matrix
int nc,nr;
string c,r;
input[0]=cleanAllSpace(input[0]);
r = input[0].substr(input[0].find("(")+1,input[0].find(",")-input[0].find("(")-1);
c = input[0].substr(input[0].find(",")+1,input[0].find(")")-input[0].find(",")-1);
nr = stof(r);
nc = stof(c);
if(input[0].find("rand")>0 && input[0].find("rand")<10){
//cout<<"r: "<<r<<" c: "<<c<<endl;
varValues[nV] = CMatrix(nr,nc,CMatrix::MI_RAND);
cout<<vars[nV]<<" = "<<endl<< varValues[nV] <<endl;
}
else if(input[0].find("eye")>0 && input[0].find("eye")<10){
varValues[nV] = CMatrix(nr,nc,CMatrix::MI_EYE);
cout<<vars[nV]<<" = "<<endl<< varValues[nV] <<endl;
}
else if(input[0].find("zeros")>0 && input[0].find("zeros")<10){
varValues[nV] = CMatrix(nr,nc,CMatrix::MI_ZEROS);
cout<<vars[nV]<<" = "<<endl<< varValues[nV] <<endl;
}
else if(input[0].find("ones")>0 && input[0].find("ones")<10){
varValues[nV] = CMatrix(nr,nc,CMatrix::MI_ONES);
cout<<vars[nV]<<" = "<<endl<< varValues[nV] <<endl;
}
}
/*for(int i=0; i<n;i++){
    cout<<varsInOperation[i]<<"&&&";
}cout<<n<<endl;*/
else if(numExist(input[0])){ // equal number
input[0] = cleanAllSpace(input[0]);
string s = input[0].substr(input[0].find("=")+1);
//cout<<s<<endl;
varValues[nV] = stof(s);
cout<<vars[nV]<<" = "<<endl<< varValues[nV] <<endl;
}
else if(isThereChars(input[0])){ // equal with another CMatrix
input[0] = cleanAllSpace(input[0]);
int pos = input[0].find("=");
string s = input[0].substr(pos+1);
int n = pos_search(vars,s);
varValues[nV] = varValues[n];
cout<<vars[nV]<<" = "<<endl<< varValues[nV] <<endl;
}
else { // return R*C Matrix

}
   }
   else if(isThereChars(input[0])){ // print var line
   cout<<"Variable Does Not Exist!"<<endl;
   nV--;
   }
   else{nV--;cout<<"You don't write any thing!"<<endl;} //for empty
nV++;
varExists = 0;
}else{  //------------ var exist -----------------//
input[0] = cleanAllSpace(input[0]);
int n = pos_search(vars,input[0]);
   if(isThereChars(input[0]) && !operationExist(input[0]) && !numExist(input[0])){ // print var line
    cout<<vars[n]<<" = "<<endl<< varValues[n] <<endl;
   }
   else{
vars.erase(vars.begin()+n);
varValues[n] = 0;
   varExists = 1;
   nV--;
   }
}
}}
else{cout<<"File Does Not Open"<<endl;}
//-------------------cin input and press zero to exit--------------------------------------------------------
do{
    if(!varExists)getline(cin,input[0]);
    cout<<"Input: "<<input[0]<<endl;
    input[0] = cleanString(input[0]);
    int semicolon = input[0].find(";");
if(semicolon>0)input[0].erase(semicolon,1);
  //  cout<<input[0]<<endl;
    string tvar = varChar(input[0]);
  //  cout <<tvar<<" " <<exist(vars,tvar)<<endl;
    if(!exist(vars,tvar)){ //var not exist
    //        cout<<"Not existsssssssssssss"<<endl;
        if(char_exist(input[0],"=")){ //for multi-line
                vars.push_back(tvar);
    //            cout<<"**"<<tvar<<endl;
    }
    int inputBegNum = countChar(input[0],'[');
    int inputEndNum = countChar(input[0],']');
    if((inputBegNum>0||inputEndNum>0)&&(inputBegNum == inputEndNum)&&(nLine == 1)){ //check for one line input
      nLine = 1;
      //cout<<"one line input!"<<endl;
    }else if(inputBegNum>0||inputEndNum>0){ //check for multi-line input
      //cout<<"multi-line input!"<<endl;
       if(nLine==1){input[1] = input[0];
       nLine = 2;}
       else{
       cout<<"this is the full line"<<endl<<input[1]<<endl<<input[0]<<endl;
        nLine = 1;nV--;}}
   else if(char_exist(input[0],"=")){ // this is operation
   //cout<<"operation!"<<endl;
   vector <string> varsInOperation;
   int n = 0;
charsExistInString(input[0],varsInOperation,n); // know all matrix variables in the operation
if(n == 0 && operationExist(input[0])){ // return 1*1 matrix
int a = countChar(input[0],'(');
int b = countChar(input[0],')');
if(a != b){
    cout<<"Invalid Input!"<<endl;
}
else{
varValues[nV] = oneToOneOperationCalculation(input[0]);
cout <<vars[nV]<<" = "<<endl<<varValues[nV]<<endl;}
}
else if (n==0 && isTherechars(input[0])){ // return MI Matrix
int nc,nr;
string c,r;
input[0]=cleanAllSpace(input[0]);
r = input[0].substr(input[0].find("(")+1,input[0].find(",")-input[0].find("(")-1);
c = input[0].substr(input[0].find(",")+1,input[0].find(")")-input[0].find(",")-1);
nr = stof(r);
nc = stof(c);
if(input[0].find("rand")>0 && input[0].find("rand")<10){
//cout<<"r: "<<r<<" c: "<<c<<endl;
varValues[nV] = CMatrix(nr,nc,CMatrix::MI_RAND);
cout<<vars[nV]<<" = "<<endl<< varValues[nV] <<endl;
}
else if(input[0].find("eye")>0 && input[0].find("eye")<10){
varValues[nV] = CMatrix(nr,nc,CMatrix::MI_EYE);
cout<<vars[nV]<<" = "<<endl<< varValues[nV] <<endl;
}
else if(input[0].find("zeros")>0 && input[0].find("zeros")<10){
varValues[nV] = CMatrix(nr,nc,CMatrix::MI_ZEROS);
cout<<vars[nV]<<" = "<<endl<< varValues[nV] <<endl;
}
else if(input[0].find("ones")>0 && input[0].find("ones")<10){
varValues[nV] = CMatrix(nr,nc,CMatrix::MI_ONES);
cout<<vars[nV]<<" = "<<endl<< varValues[nV] <<endl;
}
}
/*for(int i=0; i<n;i++){
    cout<<varsInOperation[i]<<"&&&";
}cout<<n<<endl;*/
else if(numExist(input[0])){ // equal number
      //  cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
input[0] = cleanAllSpace(input[0]);
string s = input[0].substr(input[0].find("=")+1);
//cout<<s<<endl;
varValues[nV] = stof(s);
cout<<vars[nV]<<" = "<<endl<< varValues[nV] <<endl;
}
else if(isThereChars(input[0])){ // equal with another CMatrix
input[0] = cleanAllSpace(input[0]);
int pos = input[0].find("=");
string s = input[0].substr(pos+1);
int n = pos_search(vars,s);
varValues[nV] = varValues[n];
cout<<vars[nV]<<" = "<<endl<< varValues[nV] <<endl;
}
else { // return R*C Matrix

}
   }
   else if(isThereChars(input[0])){ // print var line
   cout<<"Variable Does Not Exist!"<<endl;
   nV--;
   }
   else{nV--;cout<<"You don't write any thing!"<<endl;} //for empty
nV++;
varExists = 0;
}else{ // var exist
input[0] = cleanAllSpace(input[0]);
int n = pos_search(vars,input[0]);
   if(isThereChars(input[0]) && !operationExist(input[0]) && !numExist(input[0])){ // print var line
    cout<<vars[n]<<" = "<<endl<< varValues[n] <<endl;
   }
   else{
vars.erase(vars.begin()+n);
varValues[n] = 0;
   varExists = 1;
   nV--;
   }
}
}while(input[0] != "exit" && input[0] != "Exit" && input[0] != "0");
//CMatrix x = CMatrix("[1 2 3 4; 1 2 3 4]");
//CMatrix c = CMatrix("[5 6 7 8; 5 6 7 8]");
//c.addMatrixVer(x);
//cout<<c<<endl;
return 0;
}
