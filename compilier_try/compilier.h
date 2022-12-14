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

    // ���
    void ProgramBlock();                //��������� � �����
    void MainBlock();                   //���������
    // void ConstBlock();                  //������ ��������
    void VarBlock();                    //������ ����������
    void SimilarVars();                 //���������� ����������
    void CompositeOperatorBlock();      //��������� �������� (begin, end)
    void OperatorBlock();               //��������
    void SimpleOperatorBlock();         //������� ��������
    void ComplicatedOperatorBlock();    //������� ��������
    void AssignOperatorBlock();         //�������� ������������
    VarType Expression();               //���������
    VarType SimpleExpression();         //������� ���������
    VarType Term();                     //���������
    VarType Multiplier();               //���������
    void ConditionalOperatorBlock();    //�������� ��������
    void WhileBlock();                  //���� � ������������
    void WriteLnBlock();                //writeln - ����� �� �������
    void ReadLnBlock();                 //readln - ���� � �������
public:
    CLexer* lexer = nullptr;
    CCompilier(const char* In, const char* Out);
    
    void Run();
};