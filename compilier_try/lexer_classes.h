#pragma once
#include "inout.h"

// template<typename T, typename... Params>
// std::unique_ptr<T> CreatePtr(Params... parameters)
// {
// 	return std::make_unique<T>(parameters...);
// }

enum TokenTp { Constant, Identifier, KeyWord, Operator };
enum VarType { DefaultType, IntegerType, FloatType, StringType, BoolType };
enum KeyWordType {
    ProgramKW, VarKW, IfKW, ConstKW, ThenKW,
    ElseKW, ForKW, WhileKW, DoKW, BeginKW, EndKW,
    ReadKW, WriteKW, IntegerKW, FloatKW, StringKW, BoolKW, ReadlnKW, WritelnKW
};
enum OperatorType {
    OType1, OType2, OType3, OType4, OType5, OType6, OType7,
    OType8, OType9, OType10, OType11, OType12, OType13, OType14,
    OType15, OType16, OType17, OType18, OType19, OType20, OType21,
    OType22
};

extern std::map<std::string, OperatorType> from_str_to_operator;
extern std::map<OperatorType, std::string> from_operator_to_str;
extern std::map<std::string, KeyWordType> from_str_to_kw;
extern std::map<KeyWordType, std::string> from_kw_to_str;

std::string make_low(std::string a);

bool can_cast(VarType from, VarType to);

class CVariant;


class CToken
{
public:
    TokenTp tt;
    TextPos pos;
    CToken();
    CToken(TokenTp tt, TextPos pos);
    virtual std::string ToString() = 0;
    ~CToken() {};
};

class CConstToken : public CToken
{
public:
    std::unique_ptr<CVariant> value;
    CConstToken();
    CConstToken(std::string lexem);
    CConstToken(TextPos position, std::string lexem);
    std::string ToString() override;
    ~CConstToken() {}
};

class CIdentToken : public CToken
{
public:
    std::string value;
    CIdentToken();
    CIdentToken(std::string lexem);
    CIdentToken(TextPos position, std::string lexem);
    std::string ToString() override;
};

class CKeyWordToken : public CToken
{
public:
    KeyWordType value;
    CKeyWordToken(std::string lexem);
    CKeyWordToken(TextPos position, std::string lexem);
    std::string ToString() override;
};

class COperatorToken : public CToken
{
public:
    OperatorType value;
    COperatorToken();
    COperatorToken(std::string lexem);
    COperatorToken(TextPos position, std::string lexem);
    std::string ToString() override;
};

class CVariant
{
public:
    VarType vt;
    CVariant();
    CVariant(VarType vt);
    virtual std::string ToString() = 0;
    ~CVariant() {}
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