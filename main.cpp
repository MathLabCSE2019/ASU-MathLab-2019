#include "MathLab.h"
#include "MathLap.cpp"
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
using namespace std;

CMatrix dummy_matrix;
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
    if( !x[i].compare(c)){
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

string operation(string x){
string y = "";
if(char_exist(x,"+")){
    y +="+";
}
else if(char_exist(x,"-")){
    y +="-";
}
else if(char_exist(x,"^")){
    y +="^";
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


int char_pos(string x,char c){
int pos;
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
       dummy_matrix = b;
        c=a;
        c.div(dummy_matrix);
        cout<<endl<<c<<endl;
       }
       else if(o==".*"){
        c =  a.element_mul(b);
        cout<<endl<<c<<endl;
       }
       else if(o == "\'"){
        dummy_matrix.getTranspose(a);
        c=dummy_matrix;
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
        cout<< "NO";
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
        else if(o== "^"){
        b=-2;
        c = a^(int)b;
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


int main (int argc, char* argv[]){
    //---------------------input---------------------------------------------------------------------
vector <string> vars;
CMatrix varValues[1000];
int i = 0 ;
string input = "";
//----file-------------------------
ifstream testFile("example.m");
      if(testFile.is_open()){

            while( !testFile.eof() ){
                getline(testFile,input);
                         string temp ="";
        bool eq_exist = char_exist(input,"=");
        if(eq_exist){
           bool op_exist = char_exist(input,"+") ||char_exist(input,"-")||char_exist(input,"*")||char_exist(input,"/")||char_exist(input,"./")||char_exist(input,".*")||char_exist(input,"\'");
           string tvar = varChar(input);
           if(!exist(vars,tvar)){ //var not exist
                vars.push_back(tvar);
                if(char_exist(input,"[")&&(op_exist==false)){ //initialize matrix
                    temp = input.substr(input.find_first_of("["),input.find_last_of("]")-input.find_first_of("[")+1);

                    CMatrix tmat; //NEED TO CHANGE ACCORDING TO CLASS!!!
                    tmat = temp; //NEED TO CHANGE ACCORDING TO CLASS!!!

                    varValues[i]= tmat; //NEED TO CHANGE ACCORDING TO CLASS!!!
                i++;
                }
                else{
                    cout<<endl<<tvar<<" = ";
                    string tvar1,tvar2;
                    string op = operation(input); //determine operation
                    tvar1 = aVarChar(input,true); //find first var of operation
                    tvar2 = aVarChar(input,false);
                    if(numExist(tvar1)){
                        int pos2 = pos_search(vars,tvar2); //find second var of operation
                        double var1 = atof(tvar1.c_str());
                        CMatrix tmat ;
                        opCalc(var1,varValues[pos2],tmat,op);
                        varValues[i] = tmat;
                        i++;

                    }
                    else if(numExist(tvar2)){
                        int pos1 = pos_search(vars,tvar1); //find first var of operation
                        double var2 = atof(tvar2.c_str());
                        CMatrix tmat ;
                        opCalc(varValues[pos1],var2,tmat,op);
                        varValues[i] = tmat;
                        i++;
                    }
                    else{
                        int pos1 = pos_search(vars,tvar1);
                        int pos2 = pos_search(vars,tvar2); //find second var of operation
                        CMatrix tmat;

                        pos2 = (tvar1 == tvar2) ? pos1 : ((pos1==pos2)?pos2+1:pos2);

                        opCalc(varValues[pos1],varValues[pos2],tmat,op);
                        varValues[i] = tmat;
                        i++;
                    }
                }
           }
           else{ //var exist
                if(char_exist(input,"[")&&(op_exist==false)){ //change value of matrix
                    int pos = pos_search(vars,tvar);
                    temp = input.substr(input.find_first_of("["),input.find_last_of("]")-input.find_first_of("[")+1);
                    CMatrix tmat; //NEED TO CHANGE ACCORDING TO CLASS!!!
                    tmat = temp; //NEED TO CHANGE ACCORDING TO CLASS!!!
                    varValues[pos]=tmat;
                }
                else{
                    cout<<endl<<tvar<<" = ";
                    int pos = pos_search(vars,tvar);
                    string tvar1,tvar2;
                    string op = operation(input); //determine operation
                    tvar1 = aVarChar(input,true); //find first var of operation
                    tvar2 = aVarChar(input,false);
                    if(numExist(tvar1)){
                        int pos2 = pos_search(vars,tvar2); //find second var of operation
                        double var1 = atof(tvar1.c_str());
                        CMatrix tmat ;
                        opCalc(var1,varValues[pos2],tmat,op);
                        varValues[pos]= tmat;

                    }
                    else if(numExist(tvar2)){
                        int pos1 = pos_search(vars,tvar1); //find first var of operation
                        double var2 = atof(tvar2.c_str());
                        CMatrix tmat ;
                        opCalc(varValues[pos1],var2,tmat,op);
                        varValues[pos]= tmat;
                    }
                    else{
                        int pos1 = pos_search(vars,tvar1);
                        int pos2 = pos_search(vars,tvar2); //find second var of operation
                        CMatrix tmat ;
                        opCalc(varValues[pos1],varValues[pos2],tmat,op);
                        varValues[pos]= tmat;
                    }
                }
           }
        }

            }
       testFile.close();
      }else {cout<<"File in not open"<<endl;}
//--------Cin -------------------------
    do{

        getline(cin,input);
         string temp ="";
        bool eq_exist = char_exist(input,"=");
        if(eq_exist){
           bool op_exist = char_exist(input,"+") ||char_exist(input,"-")||char_exist(input,"*")||char_exist(input,"/")||char_exist(input,"./")||char_exist(input,".*")||char_exist(input,"\'");
           string tvar = varChar(input);
           if(!exist(vars,tvar)){ //var not exist
                vars.push_back(tvar);
                if(char_exist(input,"[")&&(op_exist==false)){ //initialize matrix
                    temp = input.substr(input.find_first_of("["),input.find_last_of("]")-input.find_first_of("[")+1);
                    CMatrix tmat; //NEED TO CHANGE ACCORDING TO CLASS!!!
                    tmat = temp; //NEED TO CHANGE ACCORDING TO CLASS!!!
                    varValues[i]= tmat; //NEED TO CHANGE ACCORDING TO CLASS!!!
                i++;}
                else{
                    cout<<endl<<tvar<<" = ";
                    string tvar1,tvar2;
                    string op = operation(input); //determine operation
                    tvar1 = aVarChar(input,true); //find first var of operation
                    tvar2 = aVarChar(input,false);
                    if(numExist(tvar1)){
                        int pos2 = pos_search(vars,tvar2); //find second var of operation
                        double var1 = atof(tvar1.c_str());
                        CMatrix tmat ;
                        opCalc(var1,varValues[pos2],tmat,op);
                        varValues[i] = tmat;
                        i++;

                    }
                    else if(numExist(tvar2)){
                        int pos1 = pos_search(vars,tvar1); //find first var of operation
                        double var2 = atof(tvar2.c_str());
                        CMatrix tmat ;
                        opCalc(varValues[pos1],var2,tmat,op);
                        varValues[i] = tmat;
                        i++;
                    }
                    else{
                        int pos1 = pos_search(vars,tvar1);
                        int pos2 = pos_search(vars,tvar2); //find second var of operation
                        CMatrix tmat ;
                        opCalc(varValues[pos1],varValues[pos2],tmat,op);
                        varValues[i] = tmat;
                        i++;
                    }
                }
           }
           else{ //var exist
                if(char_exist(input,"[")&&(op_exist==false)){ //change value of matrix
                    int pos = pos_search(vars,tvar);
                    temp = input.substr(input.find_first_of("["),input.find_last_of("]")-input.find_first_of("[")+1);
                    CMatrix tmat; //NEED TO CHANGE ACCORDING TO CLASS!!!
                    tmat = temp; //NEED TO CHANGE ACCORDING TO CLASS!!!
                    varValues[pos]=tmat;
                }
                else{

                    cout<<endl<<tvar<<" = ";
                    int pos = pos_search(vars,tvar);
                    string tvar1,tvar2;
                    string op = operation(input); //determine operation
                    tvar1 = aVarChar(input,true); //find first var of operation
                    tvar2 = aVarChar(input,false);
                    if(numExist(tvar1)){
                        int pos2 = pos_search(vars,tvar2); //find second var of operation
                        double var1 = atof(tvar1.c_str());
                        CMatrix tmat ;
                        opCalc(var1,varValues[pos2],tmat,op);
                        varValues[pos]= tmat;

                    }
                    else if(numExist(tvar2)){
                        int pos1 = pos_search(vars,tvar1); //find first var of operation
                        double var2 = atof(tvar2.c_str());
                        CMatrix tmat ;
                        opCalc(varValues[pos1],var2,tmat,op);
                        varValues[pos]= tmat;
                    }
                    else{
                        int pos1 = pos_search(vars,tvar1);
                        int pos2 = pos_search(vars,tvar2); //find second var of operation
                        CMatrix tmat ;
                        opCalc(varValues[pos1],varValues[pos2],tmat,op);
                        varValues[pos]= tmat;
                    }


                }
           }
        }

    }while(input != "exit" && input != "Exit" && input != "0");

return 0;
}
