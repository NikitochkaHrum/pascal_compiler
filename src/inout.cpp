#include <bits/stdc++.h>
#include "inout.h"

std::vector<std::pair<std::string, TextPos>> getLexems(const char * In, const char * Out){
    freopen(In, "r", stdin);
    if(Out!="")
        freopen(Out, "w", stdout);
    std::vector<std::pair<std::string, TextPos>> res;
    std::string cur="", s;
    TextPos pos;
    while(getline(std::cin, s)){
        int comment=0;
        for(int i = 0; i<s.length(); i++){
            if(comment)
                continue;
            if(s[i]=='{'){
                if(cur!=""){
                    res.push_back(std::make_pair(cur, pos));
                    cur="";
                }
                comment++;
                continue;
            }
            if(s[i]=='}'){
                comment--;
                continue;
            }
            if(s[i]==' ' || s[i]==';'){
                if(cur!=""){
                    res.push_back(std::make_pair(cur, pos));
                    cur="";
                }
                if(s[i]==';')
                    res.push_back(std::make_pair(";", TextPos(pos.line_number, i)));
                continue;
            }
            
        }
        pos.line_number++;
    }
    return res;
}


int main(){
    std:: cout << "sda";
}
