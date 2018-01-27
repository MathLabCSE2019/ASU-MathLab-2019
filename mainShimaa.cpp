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
}}
else{cout<<"File Does Not Open"<<endl;}
return 0;
}
