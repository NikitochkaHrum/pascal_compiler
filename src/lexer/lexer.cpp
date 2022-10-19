#include "lexer.h"
#include "classes.h"

CLexer::CLexer(const char * In, const char * Out){
    InOut = std::make_unique<InOutModule>(In, Out);
}

std::unique_ptr<CToken> CLexer::GetNextToken(){
    auto lexem = InOut->GetNextLex();
    while(lexem.first == " " && lexem != END_LEXEMS){
        lexem = InOut->GetNextLex();
    }
    if(lexem == END_LEXEMS) return nullptr;

    auto low_lexem = make_low(lexem.first);
    for(const auto& [k, v] : from_str_to_kw){
        if(k==low_lexem)
            return std::make_unique<CKeyWordToken>(lexem.second, lexem.first);
    }

    for(const auto& [k, v] : from_str_to_operator){
        if(k==low_lexem)
            return std::make_unique<COperatorToken>(lexem.second, lexem.first);
    }
    bool can = false;
    try {
        auto smth = stof(lexem.first);
        can=true;
    }
    catch(std::invalid_argument& e){ }
    if(!can && !(low_lexem[0]==low_lexem[low_lexem.length()-1] && low_lexem[0]=='"') && low_lexem!="true" && low_lexem!="false")
        return std::make_unique<CIdentToken>(lexem.second, lexem.first);
    return std::make_unique<CConstToken>(lexem.second, lexem.first);
}