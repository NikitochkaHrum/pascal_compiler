#include "inout.h"

InOutModule::InOutModule(const char * In, const char * Out){
    freopen(In, "r", stdin);
    if(Out!="")
        freopen(Out, "w", stdout);
    cur="";
    idx=0;
    comment=0;
    pos.char_number=0;
    pos.line_number=0;
    ready = getline(std::cin, s) ? true : false;
}

std::pair<std::string, TextPos> InOutModule::GetNextLex(){
    if(!ready){
        // throw EOF flag
        return END;
    }
    for(; idx<s.length(); idx++){
        if(comment)
            continue;
        if(s[idx]=='{'){
            comment++;
            if(cur!=""){
                auto ans = std::make_pair(cur, pos);
                cur="";
                idx++;
                return ans;
            }
            continue;
        }
        if(s[idx]=='}'){
            comment--;
            continue;
        }
        if(s[idx]==':'){
            if(cur!=""){
                auto ans = std::make_pair(cur, pos);
                cur="";
                return ans;
            }
            cur=":";
            pos.char_number=idx;
            if(idx==s.length()-1 || s[idx+1]!='='){
                auto ans = std::make_pair(std::string(1, s[idx]), pos);
                cur="";
                idx++;
                return ans;
            }
            continue;
        }
        if(s[idx]==' ' || s[idx]==';' || s[idx]==',' || s[idx]=='\t' || s[idx]=='\n' || s[idx]=='(' || s[idx]==')'){
            if(cur!=""){
                auto ans = std::make_pair(cur, pos);
                cur="";
                return ans;
            }
            if(s[idx]!=' ' && s[idx]!='\t' && s[idx]!='\n'){
                auto ans = std::make_pair(std::string(1, s[idx]), TextPos(pos.line_number, idx));
                idx++;
                return ans;
            }
            continue;
        }
        if(cur==""){
            pos.char_number=idx;
        }
        cur+=s[idx];
    }
    bool have_ans=false;
    auto ans = std::make_pair(cur, pos);
    if(cur!=""){
        have_ans=true;
        cur="";
    }
    idx=0;
    pos.line_number++;
    ready = getline(std::cin, s) ? true : false;
    if(have_ans)
        return ans;
    return this->GetNextLex();
}

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
                if(i==s.length()-1 || s[i+1]!='='){
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
    std::cout << "TEST\n";
    InOutModule InOut("/home/pna/Documents/study/pascal_compiler/src/input.txt");
    std::pair<std::string, TextPos> a=InOut.GetNextLex();
    do{
        std::cout << a.first << '\n';
        std::cout << a.second.line_number << ' ' << a.second.char_number << "\n\n";
        a=InOut.GetNextLex();
    }while(a!=END);
    
    // for(auto a: res){
    //     std::cout << a.first << '\n';
    //     std::cout << a.second.line_number << ' ' << a.second.char_number << "\n\n";
    // }
}
