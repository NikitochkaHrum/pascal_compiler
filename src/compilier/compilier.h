#pragma once
#include "../exceptions/exceptions.h"
#include "../lexer/lexer.h"

class CCompilier
{
private:
    std::unique_ptr<CLexer> lexer = nullptr;
    std::unique_ptr<CToken> token = nullptr;
    std::unique_ptr<CToken> GetNextToken();
public:
    CCompilier(const char * In, const char * Out="");
    void Accept(std::unique_ptr<CToken> expected_token);
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
};