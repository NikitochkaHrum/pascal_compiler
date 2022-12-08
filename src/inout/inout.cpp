#include "inout.h"

InOutModule::InOutModule(const char * In, const char * Out){
    freopen(In, "r", stdin);

    if(Out[0]!='\0')
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
        return END_LEXEMS;
    }
    for(; idx<s.length(); idx++){
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
        if(comment)
            continue;
        if(s[idx]=='.'){
            if(!idx || s[idx-1]<'0' || s[idx-1]>'9'){
                if(cur!=""){
                    auto ans = std::make_pair(cur, pos);
                    cur="";
                    return ans;
                }
                pos.char_number=idx;
                auto ans = std::make_pair(std::string(1, s[idx]), pos);
                idx++;
                return ans;
            }
            cur+=s[idx];
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
        if(s[idx]=='<'){
            if(cur!=""){
                auto ans = std::make_pair(cur, pos);
                cur="";
                return ans;
            }
            cur="<";
            pos.char_number=idx;
            if(idx==s.length()-1 || s[idx+1]!='>'){
                auto ans = std::make_pair(std::string(1, s[idx]), pos);
                cur="";
                idx++;
                return ans;
            }
            continue;
        }
        if(s[idx]=='>'){
            if(cur!="" && cur!="<"){
                auto ans = std::make_pair(cur, pos);
                cur="";
                return ans;
            }
            if(cur=="<"){
                cur+=s[idx];
                auto ans = std::make_pair(cur, pos);
                idx++;
                cur="";
                return ans;
            }
            pos.char_number=idx;
            auto ans = std::make_pair(std::string(1, s[idx]), pos);
            idx++;
            cur="";
            return ans;
        }
        
        if(s[idx]=='='){
            if(cur==">" || cur=="<" || cur==":"){
                cur+=s[idx];
                auto ans = std::make_pair(cur, pos);
                idx++;
                cur="";
                return ans;
            }
            else{
                auto ans = std::make_pair(std::string(1, s[idx]), TextPos(pos.line_number, idx));
                idx++;
                cur="";
                return ans;
            }
        }
        if(s[idx]==' ' || s[idx]==';' || s[idx]==',' || s[idx]=='\t' || s[idx]=='\n' || s[idx]=='(' || s[idx]==')' || s[idx]=='+' || s[idx]=='-' || s[idx]=='*' || s[idx]=='/'){
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
        // if(idx && (s[idx-1]=='=' || s[idx-1]=='>' || s[idx-1]=='<' || s[idx-1]=='+' || s[idx-1]=='-')){
        //     if(cur!=""){
        //         auto ans = std::make_pair(cur, pos);
        //         cur="";
        //         return ans;
        //     }
        // }
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

void InOutModule::print_semantic_errors(ErrorHandler h){
    auto my_errors = h.get_errors();
    for(auto e: my_errors){
        std::cout << "Info: " << e.info << "\n\tPos: " << e.pos.line_number+1 << ' ' << e.pos.char_number+1 << "\n\n";
    }
}