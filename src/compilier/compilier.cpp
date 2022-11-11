#include "compilier.h"

CCompilier::CCompilier(const char * In, const char * Out){
    lexer = std::make_unique<CLexer>(In, Out);
}

std::unique_ptr<CToken> CCompilier::GetNextToken(){
    return lexer->GetNextToken();
}

void CCompilier::Accept(std::unique_ptr<CToken> expected_token){
    if(expected_token->tt != token->tt){
        throw CTokenExpectedException(expected_token->tt, token->pos);
    }
    if(expected_token->tt == KeyWord){
        auto our = static_cast<CKeyWordToken*>(token.get());
        auto exp = static_cast<CKeyWordToken*>(expected_token.get());
        KeyWordType kw1 = our->value, kw2 = exp->value;
        delete our;
        delete exp;
        if(kw1!=kw2)
            throw CTokenExpectedException(expected_token->tt, token->pos); // TODO другой констуктор для KeyWord
    }
    token = GetNextToken();
}

int main(){
    return 0;
}