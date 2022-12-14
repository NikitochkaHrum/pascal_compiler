#pragma once

#include "exceptions.h"
#include "error_handler.h"
#include "lexer.h"
#include <memory>
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Threading;
using namespace System::Reflection::Emit;
using namespace System::Reflection;
using System::Reflection::AssemblyName;
using namespace msclr::interop;



ref class CCompilier
{
private:
    ILGenerator^ Gen;
    Dictionary<String^, LocalBuilder^> vars_lb;
    Dictionary<String^, Type^> vars;
    CToken* token;
    ErrorHandler* handler;
    void emit_op(OperatorType op);
    String^ convert_to_mstr(std::string s);
    Type^ GetType(VarType v);
    VarType GetType(Type^ v);
    CToken* GetNextToken();
    void ChangeSign(System::Type^ type);
    void LoadValue(CToken* t);
    void DoWriteLn(Type^ t);
    void DoReadLn(CToken* tk);
    void Accept(TokenTp expected_token_type);
    void Accept(OperatorType expected_operator);
    void Accept(KeyWordType expected_keyword);
    void Accept(VarType expected_var_type);
    void Add_var(std::string& name, VarType type);
    VarType Derive(VarType left, VarType right, OperatorType last_operation, TextPos pos_for_error);

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
    void WhileBlock();                  //Цикл с предусловием
    void WriteLnBlock();                //writeln - вывод на консоль
    void ReadLnBlock();                 //readln - ввод с консоли
public:
    CLexer* lexer = nullptr;
    CCompilier(const char* In, const char* Out);
    
    void Run();
};