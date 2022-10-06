#include "inout.h"

std::vector<std::pair<std::string, TextPos>> getLexems(const char * In, const char * Out){
    freopen(In, "r", stdin);
    if(Out!="")
        freopen(Out, "w", stdout);
    std::vector<std::pair<std::string, TextPos>> res;
    std::string cur="", s;
    TextPos pos;
    while(getline(std::cin, s)){
        // std::cout<< s<< '\n';
        int comment=0;
        // for(int i = 0; i<s.length(); i++)
        //     std::cout << s[i] << ' ';
        // continue;
        for(int i = 0; i<s.length(); i++){
            if(comment)
                continue;
            // std::cout << cur << '\n';
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
            if(s[i]==':'){
                if(cur!=""){
                    res.push_back(std::make_pair(cur, pos));
                }
                cur=":";
                pos.char_number=i;
                if(i<s.length()-1 && s[i+1]!='='){
                    res.push_back(std::make_pair(std::string(1, s[i]), pos));
                    cur="";
                }
                continue;
            }
            if(s[i]==' ' || s[i]==';' || s[i]==',' || s[i]=='\t' || s[i]=='\n' || s[i]=='(' || s[i]==')'){
                if(cur!=""){
                    res.push_back(std::make_pair(cur, pos));
                    cur="";
                }
                // if(s[i]==',')
                //     std::cout << std::string(1, s[i-1]) << ",\n";
                if(s[i]!=' ' && s[i]!='\t' && s[i]!='\n')
                    res.push_back(std::make_pair(std::string(1, s[i]), TextPos(pos.line_number, i)));
                continue;
            }
            if(cur==""){
                pos.char_number=i;
            }
            cur+=s[i];
        }
        if(cur!=""){
            res.push_back(std::make_pair(cur, pos));
            cur="";
        }
        pos.line_number++;
    }
    return res;
}


int main(){
    auto res = getLexems("/home/pna/Documents/study/pascal_compiler/src/input.txt");
    for(auto a: res){
        std::cout << a.first << '\n';
        std::cout << a.second.line_number << ' ' << a.second.char_number << "\n\n";
    }
}
