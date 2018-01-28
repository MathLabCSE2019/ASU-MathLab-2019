bool isThereChars(string s){
if(char_exist(s,"A")||char_exist(s,"B")||char_exist(s,"C")||char_exist(s,"D")||char_exist(s,"E")||char_exist(s,"F")||char_exist(s,"G")||char_exist(s,"H")||char_exist(s,"I"))return true;
if(char_exist(s,"J")||char_exist(s,"K")||char_exist(s,"L")||char_exist(s,"M")||char_exist(s,"N")||char_exist(s,"O")||char_exist(s,"P")||char_exist(s,"Q")||char_exist(s,"R"))return true;
if(char_exist(s,"S")||char_exist(s,"T")||char_exist(s,"U")||char_exist(s,"V")||char_exist(s,"W")||char_exist(s,"X")||char_exist(s,"Y")||char_exist(s,"Z"))return true;
else return false;
}
string cleanAllSpace(string x){ for(int i =0; i<x.size(); i++){ if(x.substr(i,1)==" "){x.erase(i,1);}} return x;}
void charsExistInString(string s,vector <string> &x,int &n){
    int equality = s.find("=");
    s = s.substr(equality+1);
  if(char_exist(s,"A")){x.push_back("A");n++;}
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
}
int main (int argc, char* argv[]){
    //---------------------input---------------------------------------------------------------------
vector <string> vars;
CMatrix varValues[1000];
int nV = 0 ;
    string input[10] = ""; //for multi-line input
    int nLine = 1; // number of line in any input
    //-------------------read input from file--------------------------------------------------------
ifstream in ("advexample.m");
if(in.is_open()){
    while( !in.eof() ){
    getline(in,input[0]);
    cout<<input[0]<<endl;
    input[0] = cleanString(input[0]);
    cout<<input[0]<<endl;
    string tvar = varChar(input[0]);
    if(!exist(vars,tvar)){ //var not exist
        if(char_exist(input[0],"=")){ //for multi-line
                vars.push_back(tvar);
                cout<<"**"<<tvar<<endl;}
    int inputBegNum = countChar(input[0],'[');
    int inputEndNum = countChar(input[0],']');
    if((inputBegNum>0||inputEndNum>0)&&(inputBegNum == inputEndNum)&&(nLine == 1)){ //check for one line input
      nLine = 1;
      cout<<"one line input!"<<endl;
    }else if(inputBegNum>0||inputEndNum>0){ //check for multi-line input
      cout<<"multi-line input!"<<endl;
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
varValues[nV] = oneToOneOperationCalculation(input[0]);
//cout << varValues[nV]<<endl;
}
else if (n==0){ // return MI Matrix

}
/*for(int i=0; i<n;i++){
    cout<<varsInOperation[i]<<"&&&";
}cout<<n<<endl;*/
else { // return R*C Matrix

}
   }
   else if(isThereChars(input[0])){ // print var line
   cout<<"Variable Does Not Exist!"<<endl;
   nV--;
   }
   else{nV--;cout<<"You don't write any thing!"<<endl;} //for empty
nV++;
}else{ // var exist
   if(input[0]!="" && input[0] != "\n"){ // print var line
    int pos = pos_search(vars,tvar);
    cout<<"var exist at pos "<<pos<<endl;
   }
}
}}
else{cout<<"File Does Not Open"<<endl;}
return 0;
}
