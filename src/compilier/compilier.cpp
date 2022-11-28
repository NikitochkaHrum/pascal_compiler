#include "compilier.h"

CCompilier::CCompilier(const char * In, const char * Out){
    lexer = std::make_unique<CLexer>(In, Out);
}

void CCompilier::Run(){
    token = lexer->GetNextToken();
    try{
        ProgramBlock();
    }
    catch(CTokenExpectedException& exc){
        std::cout << exc.what();
    }
}

std::unique_ptr<CToken> CCompilier::GetNextToken(){
    return lexer->GetNextToken();
}

void CCompilier::Accept(TokenType expected_token_type){
    if(token->tt!=expected_token_type)
        throw CTokenExpectedException(expected_token_type, token->pos);
    token = GetNextToken();
}

void CCompilier::Accept(OperatorType expected_operator){
    if(token->tt!=Operator)
        throw CTokenExpectedException(Operator, token->pos);;
    auto our = static_cast<COperatorToken*>(token.get());
    if(our->value!=expected_operator)
        throw CTokenExpectedException(Operator, token->pos);
    token = GetNextToken();
}

void CCompilier::Accept(KeyWordType expected_keyword){
    if(token->tt!=KeyWord)
        throw CTokenExpectedException(KeyWord, token->pos);;
    auto our = static_cast<CKeyWordToken*>(token.get());
    if(our->value!=expected_keyword)
        throw CTokenExpectedException(KeyWord, token->pos);
    token = GetNextToken();
}

void CCompilier::Accept(VarType expected_var_type){
    if(token->tt!=Constant)
        throw CTokenExpectedException(Constant, token->pos);;
    auto our = static_cast<CConstToken*>(token.get());
    if(our->value->vt!=expected_var_type)
        throw CTokenExpectedException(Constant, token->pos);
    token = GetNextToken();
}

void CCompilier::ProgramBlock(){
    Accept(ProgramKW);
    Accept(Identifier);
    Accept(from_str_to_operator[";"]);
    MainBlock();
    Accept(from_str_to_operator["."]);
}

void CCompilier::MainBlock(){
                                     //TODO раздел меток
    if(token->ToString() == from_kw_to_str[ConstKW])
        ConstBlock();                //Раздел констант
                                     //TODO Раздел типов
    if(token->ToString() == from_kw_to_str[VarKW])
        VarBlock();                  //Раздел переменных
                                     //TODO Раздел процедур и функций
    CompositeOperatorBlock();        //Раздел операторов
}

void CCompilier::ConstBlock(){
    Accept(ConstKW);
    Accept(Identifier);
    Accept(from_str_to_operator["="]);
    Accept(Constant);
    Accept(from_str_to_operator[";"]);
    while(token->tt==Identifier){
        Accept(Identifier);
        Accept(from_str_to_operator["="]);
        Accept(Constant);
        Accept(from_str_to_operator[";"]);
    }
}

void CCompilier::VarBlock(){
    Accept(VarKW);

    SimilarVars(); //Раздел однотипных переменных
    Accept(from_str_to_operator[";"]);

    while(token->tt == Identifier){
        SimilarVars();
        Accept(from_str_to_operator[";"]);
    }
}

void CCompilier::SimilarVars(){
    Accept(Identifier);
    while(token->ToString()==","){
        Accept(from_str_to_operator[","]);
        Accept(Identifier);
    }
    Accept(from_str_to_operator[":"]);

    auto our = static_cast<CKeyWordToken*>(token.get());
    if(our->value!=IntegerKW)
        Accept(FloatKW);
    else
        Accept(IntegerKW);
}   

void CCompilier::CompositeOperatorBlock(){
    Accept(BeginKW);
    OperatorBlock();
    Accept(from_str_to_operator[";"]);

    while(token->tt==Identifier || token->ToString()=="begin"
         || token->ToString()=="if"){
        OperatorBlock();
        Accept(from_str_to_operator[";"]);
    }
    Accept(EndKW);
}

void CCompilier::OperatorBlock(){
    if(token->tt==Identifier)
        SimpleOperatorBlock();
    else if(token->ToString()=="begin" || token->ToString()=="if")
        ComplicatedOperatorBlock();
}

void CCompilier::SimpleOperatorBlock(){
    AssignOperatorBlock();
}

void CCompilier::AssignOperatorBlock(){
    Accept(Identifier);
    Accept(from_str_to_operator[":="]);
    Expression();
}

void CCompilier::Expression(){
    SimpleExpression();
    auto s = token->ToString();
    if(s == "=" || s == "<>" || s == "<" || s=="<=" || s==">=" || s==">"){
        Accept(from_str_to_operator[s]);
        SimpleExpression();
    }
}

void CCompilier::SimpleExpression(){
    if(token->ToString() == "+" || token->ToString() == "-"){
        Accept(from_str_to_operator[token->ToString()]);
    }
    Term();
    while(token->ToString()=="+" || token->ToString()=="-" || token->ToString()=="or"){
        Accept(Operator);
        Term();
    }
}

void CCompilier::Term(){
    Multiplier();
    while(token->ToString()=="div" || token->ToString()=="mod" || token->ToString()=="and" || token->ToString()=="*" || token->ToString()=="/"){
        Accept(Operator);
        Multiplier();
    }
}

void CCompilier::Multiplier(){
    if(token->tt==Identifier){
        Accept(Identifier);
    }
    else if(token->tt==Constant){
        Accept(Constant);
    }
    else if(token->ToString()=="("){
        Accept(from_str_to_operator["("]);
        Expression();
        Accept(from_str_to_operator[")"]);
    }
    else{
        Accept(from_str_to_operator["not"]);
        Multiplier();
    }
}

void CCompilier::ComplicatedOperatorBlock(){
    if(token->ToString()=="begin"){
        CompositeOperatorBlock();
    }
    else{ // if block
        ConditionalOperatorBlock();
    }
}

void CCompilier::ConditionalOperatorBlock(){
    Accept(IfKW);
    Expression();
    Accept(ThenKW);
    OperatorBlock();
    if(token->ToString()=="else"){
        Accept(ElseKW);
        OperatorBlock();
    }
}

int main(){
    auto compilier = std::make_unique<CCompilier>("/home/pna/Documents/study/pascal_compiler/input.txt");
    compilier->Run();
}