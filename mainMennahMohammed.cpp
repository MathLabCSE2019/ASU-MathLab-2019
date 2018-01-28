
string cleanString (string x) { for(int i =0;i<x.size();i++){ if(x.substr(i,1)==x.substr(i+1,1)&&x.substr(i,1)==" ") {x. erase(i,1) ; i--;} } return x; }
string cleanAllSpace(string x){ for(int i =0; i<x.size(); i++){ if(x.substr(i,1)==" "){x.erase(i,1);}} return x;}
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
