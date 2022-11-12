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
    Accept(std::make_unique<CIdentToken>());
    Accept(std::make_unique<COperatorToken>(";"));
    MainBlock();
    Accept(std::make_unique<COperatorToken>("."));
}

void CCompilier::MainBlock(){
                                //TODO раздел меток
    ConstBlock();               //Раздел констант
                                //TODO Раздел типов
    VarBlock();                 //Раздел переменных
    CompositeOperatorBlock();   //Раздел процедур и функций, заменённый на раздел составного оператора
                                //TODO Раздел операторов
}

void CCompilier::ConstBlock(){
    try{
        Accept(std::make_unique<CKeyWordToken>("Const"));
    }
    catch(CTokenExpectedException &e){
        return;
    }
    Accept(std::make_unique<CIdentToken>());
    Accept(std::make_unique<COperatorToken>("="));
    Accept(std::make_unique<CConstToken>());
    Accept(std::make_unique<COperatorToken>(";"));
    while(true){
        try{
            Accept(std::make_unique<CIdentToken>());
        }
        catch(CTokenExpectedException &e){
            break;
        }
        Accept(std::make_unique<COperatorToken>("="));
        Accept(std::make_unique<CConstToken>());
        Accept(std::make_unique<COperatorToken>(";"));
    }
}

void CCompilier::VarBlock(){
    try{
        Accept(std::make_unique<CKeyWordToken>("Var"));
    }
    catch(CTokenExpectedException &e){
        return;
    }
    SimilarVars(); //Раздел однотипных переменных
    Accept(std::make_unique<COperatorToken>(";"));
    while(true){
        try{
            SimilarVars();
        }
        catch(CTokenExpectedException &e){
            break;
        }
        Accept(std::make_unique<COperatorToken>(";"));
    }
}

void CCompilier::SimilarVars(){
    Accept(std::make_unique<CIdentToken>());
    while(true){
        try{
            Accept(std::make_unique<COperatorToken>(","));
        }
        catch(CTokenExpectedException &e){
            break;
        }
        Accept(std::make_unique<CIdentToken>());
    }
}   

void CCompilier::CompositeOperatorBlock(){
    Accept(std::make_unique<CKeyWordToken>("Begin"));
    OperatorBlock();
    Accept(std::make_unique<COperatorToken>(";"));
    while(true){
        try{
            OperatorBlock();
        }
        catch(CTokenExpectedException &e){
            break;
        }
        Accept(std::make_unique<COperatorToken>(";"));
    }
    Accept(std::make_unique<CKeyWordToken>("End"));
}

void CCompilier::OperatorBlock(){
    try{
        SimpleOperatorBlock();
    }
    catch(CTokenExpectedException &e){
        ComplicatedOperatorBlock();
    }
}

void CCompilier::SimpleOperatorBlock(){
    try{
        AssignOperatorBlock();
    }
    catch(CTokenExpectedException &e){
        return;
    }
}

void CCompilier::AssignOperatorBlock(){
    Accept(std::make_unique<CIdentToken>());
    Accept(std::make_unique<COperatorToken>(":="));
    Expression();
}

void CCompilier::Expression(){
    SimpleExpression();
    auto s = token->ToString();
    if(s == "=" || s == "<>" || s == "<" || s=="<=" || s==">=" || s==">"){
        Accept(std::make_unique<COperatorToken>(s));
        SimpleExpression();
    }
}

void CCompilier::SimpleExpression(){
    try{
        Accept(std::make_unique<COperatorToken>("+"));
    }
    catch(CTokenExpectedException &e){
        Accept(std::make_unique<COperatorToken>("-"));
    }
    Term();
    while(true){
        auto s = token->ToString();
        if(s=="+" || s=="-" || s=="or"){
            Accept(std::make_unique<COperatorToken>(s));
            Term();
        }
        else
            break;
    }
}

void CCompilier::Term(){
    Multiplier();
    while(true){
        auto s = token->ToString();
        if(s=="div" || s=="mod" || s=="and" || s=="*" || s=="/"){
            Accept(std::make_unique<COperatorToken>(s));
            Multiplier();
        }
        else
            break;
    }
}

void CCompilier::Multiplier(){
    if(token->tt==Identifier){
        Accept(std::make_unique<CIdentToken>());
    }
    else if(token->tt==Constant){
        Accept(std::make_unique<CConstToken>());
    }
    else if(token->ToString()=="("){
        Accept(std::make_unique<COperatorToken>("("));
        Expression();
        Accept(std::make_unique<COperatorToken>(")"));
    }
    else{
        Accept(std::make_unique<COperatorToken>("not"));
        Multiplier();
    }
}

int main(){
    return 0;
}