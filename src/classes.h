#include <bits/stdc++.h>

class TextPos
{
public:
    int line_number, char_number;
    TextPos();
    TextPos(int line_number_, int char_number_);
    
};

bool operator==(const TextPos a, const TextPos b);
bool operator!=(const TextPos a, const TextPos b);

enum TokenType {Constant, Identifier, KeyWord};
enum VarType {Int, Float, String};
enum KeyWordType {Program, Var, If, For, Else, While, begin, end, Begin, End};

class CToken
{
public:
    TokenType tt;
    virtual std::string ToString();
};

class CConstToken : public CToken
{
public:
    VarType value;
    std::string ToString() override;
};

class CIdentToken : public CToken
{
public:
    std::string value;
    std::string ToString() override;
};

class CKeyWordToken : public CToken
{
public:
    KeyWordType value;
    std::string ToString() override;
};

// class CVariant
// {
//     VarType vt;
// };