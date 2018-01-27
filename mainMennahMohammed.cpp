
string cleanString (string x) { for(int i =0;i<x.size();i++){ if(x.substr(i,1)==x.substr(i+1,1)&&x.substr(i,1)==" ") {x. erase(i,1) ; i--;} } return x; }
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
