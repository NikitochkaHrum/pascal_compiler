#pragma once
#include "../exceptions/exceptions.h"
#include "../lexer/lexer.h"

class CCompilier
{
private:
    std::unique_ptr<CToken> token = nullptr;
    std::unique_ptr<CToken> GetNextToken();
    void Accept(TokenType expected_token_type);
    void Accept(OperatorType expected_operator);
    void Accept(KeyWordType expected_keyword);
    void Accept(VarType expected_var_type);
    void ProgramBlock();                //Заголовок и точка
    void MainBlock();                   //Программа
    void ConstBlock();                  //Раздел констант
    void VarBlock();                    //Раздел переменных
    void SimilarVars();                 //Однотипные переменных
    void CompositeOperatorBlock();      //Составной оператор (begin, end)
    void OperatorBlock();               //Оператор
    void SimpleOperatorBlock();         //Простой оператор
    void ComplicatedOperatorBlock();    //Сложный оператор
    void AssignOperatorBlock();         //Оператор присваивания
    void Expression();                  //Выражение
    void SimpleExpression();            //Простое выражение
    void Term();                        //Слагаемое
    void Multiplier();                  //Множитель
    void ConditionalOperatorBlock();    //Условный оператор
public:
    std::unique_ptr<CLexer> lexer = nullptr;
    CCompilier(const char * In, const char * Out="");
    void Run();
};