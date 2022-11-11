#include "compilier.h"

CCompilier::CCompilier(const char * In, const char * Out){
    lexer = std::make_unique<CLexer>(In, Out);
    token = lexer->GetNextToken();
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
    else if(expected_token->tt == Constant){
        auto our = static_cast<CConstToken*>(token.get());
        auto exp = static_cast<CConstToken*>(expected_token.get());
        VarType vt1 = our->value->vt, vt2 = exp->value->vt;
        delete our;
        delete exp;
        if(vt1!=vt2)
            throw CTokenExpectedException(expected_token->tt, token->pos); // TODO другой констуктор для Const
    }
    token = GetNextToken();
}

void CCompilier::ProgramBlock(){
    Accept(std::make_unique<CKeyWordToken>("Program"));
    Accept(std::make_unique<COperatorToken>("."));
}

int main(){
    return 0;
}