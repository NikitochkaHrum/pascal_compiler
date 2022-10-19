#pragma once
#include "../inout/inout.h"

// template<typename T, typename... Params>
// std::unique_ptr<T> CreatePtr(Params... parameters)
// {
// 	return std::make_unique<T>(parameters...);
// }

enum TokenType {Constant, Identifier, KeyWord, Operator};
enum VarType {Int, Float, String, Bool};
enum KeyWordType {Program, Var, If, Then, Else, For, While, Do, Begin, End};
enum OperatorType {OType1, OType2, OType3, OType4, OType5, OType6, OType7, OType8, OType9, OType10, OType11};

extern std::map<std::string, OperatorType> from_str_to_operator;
extern std::map<OperatorType, std::string> from_operator_to_str;
extern std::map<std::string, KeyWordType> from_str_to_kw;
extern std::map<KeyWordType, std::string> from_kw_to_str;

std::string make_low(std::string a);

class CVariant;

class CToken
{
public:
    TokenType tt;
    TextPos pos;
    CToken();
    virtual std::string ToString() = 0;
};

class CConstToken : public CToken
{
public:
    std::unique_ptr<CVariant> value;
    CConstToken(TextPos position, std::string lexem);
    std::string ToString() override;
};

class CIdentToken : public CToken
{
public:
    std::string value;
    CIdentToken(TextPos position, std::string lexem);
    std::string ToString() override;
};

class CKeyWordToken : public CToken
{
public:
    KeyWordType value;
    CKeyWordToken(TextPos position, std::string lexem);
    std::string ToString() override;
};

class COperatorToken : public CToken
{
    OperatorType value;
    COperatorToken(TextPos position, std::string lexem);
    std::string ToString() override;
};

class CVariant
{
public:
    VarType vt;
    CVariant();
    virtual std::string ToString() = 0;
};

class CIntVariant : public CVariant
{
public:
    int source;
    CIntVariant(int source);
    std::string ToString() override;
};

class CFloatVariant : public CVariant
{
public:
    float source;
    CFloatVariant(float source);
    std::string ToString() override;
};

class CStringVariant : public CVariant
{
public:
    std::string source;
    CStringVariant(std::string source);
    std::string ToString() override;
};

class CBoolVariant : public CVariant
{
public:
    bool source;
    CBoolVariant(bool source);
    std::string ToString() override;
};