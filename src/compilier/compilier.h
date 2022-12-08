#pragma once
#include "../exceptions/exceptions.h"
#include "../exceptions/error_handler.h"
#include "../lexer/lexer.h"

class CCompilier
{
private:
    std::map<std::string, VarType> vars;
    std::map<OperatorType, TextPos> last_pos_of_op;
    OperatorType last_op;
    std::unique_ptr<CToken> token = nullptr;
    std::unique_ptr<ErrorHandler> handler = nullptr;
    std::unique_ptr<CToken> GetNextToken();
    void Accept(TokenType expected_token_type);
    void Accept(OperatorType expected_operator);
    void Accept(KeyWordType expected_keyword);
    void Accept(VarType expected_var_type);
    void Add_var(std::string& name, VarType type);
    VarType Derive (VarType left, VarType right, OperatorType last_operation, TextPos pos_for_error);

    // БНФ
    void ProgramBlock();                //Заголовок и точка
    void MainBlock();                   //Программа
    // void ConstBlock();                  //Раздел констант
    void VarBlock();                    //Раздел переменных
    void SimilarVars();                 //Однотипные переменных
    void CompositeOperatorBlock();      //Составной оператор (begin, end)
    void OperatorBlock();               //Оператор
    void SimpleOperatorBlock();         //Простой оператор
    void ComplicatedOperatorBlock();    //Сложный оператор
    void AssignOperatorBlock();         //Оператор присваивания
    VarType Expression();               //Выражение
    VarType SimpleExpression();         //Простое выражение
    VarType Term();                     //Слагаемое
    VarType Multiplier();               //Множитель
    void ConditionalOperatorBlock();    //Условный оператор
public:
    std::unique_ptr<CLexer> lexer = nullptr;
    CCompilier(const char * In, const char * Out="");
    void Run();
};