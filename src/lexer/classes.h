#pragma once
#include "../inout/inout.h"

// template<typename T, typename... Params>
// std::unique_ptr<T> CreatePtr(Params... parameters)
// {
// 	return std::make_unique<T>(parameters...);
// }

enum TokenType {Constant, Identifier, KeyWord};
enum VarType {Int, Float, String, Bool};
enum KeyWordType {Program, Var, If, Then, Else, For, While, Do, Begin, End};
std::map<std::string, KeyWordType> from_str_to_kw {
    {"program", Program},
    {"var", Var},
    {"if", If},
    {"then", Then},
    {"else", Else},
    {"for", For},
    {"while", While},
    {"do", Do},
    {"begin", Begin},
    {"end", End}
};

std::map<KeyWordType, std::string> from_kw_to_str {
    {Program, "program"},
    {Var, "var"},
    {If, "if"},
    {Then, "then"},
    {Else, "else"},
    {For, "for"},
    {While, "while"},
    {Do, "do"},
    {Begin, "begin"},
    {End, "end"}
};

using CVariantPtr = std::unique_ptr<CVariant>;

class CToken
{
public:
    TokenType tt;
    TextPos pos;
    virtual std::string ToString();
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

class CVariant
{
public:
    VarType vt;
    virtual std::string ToString();
};

class CIntVariant : public CVariant
{
public:
    int value;
    CIntVariant(int value);
    std::string ToString() override;
};

class CFloatVariant : public CVariant
{
public:
    float value;
    CFloatVariant(float value);
    std::string ToString() override;
};

class CStringVariant : public CVariant
{
public:
    std::string value;
    CStringVariant(std::string value);
    std::string ToString() override;
};

class CBoolVariant : public CVariant
{
public:
    bool value;
    CBoolVariant(bool value);
    std::string ToString() override;
};