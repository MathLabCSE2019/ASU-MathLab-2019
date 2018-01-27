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
       }}
     else if(inputBegNum>0||inputEndNum>0){ //check for multi-line input
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
   else if (n==0){ // return MI Matrix

} else { // return R*C Matrix

}
         else if(input[0]!=""){ // print var line
   cout<<"Variable Does Not Exist!"<<endl;
   nV--;
   }
   else{nV--;} //for empty
nV++;
}}
}else{ // var exist
   if(input[0]!="" && input[0] != "\n"){ // print var line
    int pos = pos_search(vars,tvar);
    cout<<"var exist at pos "<<pos<<endl;
   }
}
}}
}
else{cout<<"File Does Not Open"<<endl;}
return 0;
}
