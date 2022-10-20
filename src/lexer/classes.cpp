#include "classes.h"

std::map<std::string, OperatorType> from_str_to_operator = {
    {"+", OType1},
    {"-", OType2},
    {"*", OType3},
    {"/", OType4},
    {"mod", OType5},
    {"div", OType6},
    {"=", OType7},
    {":=", OType8},
    {":", OType9},
    {";", OType10},
    {",", OType11},
    {"(", OType12},
    {")", OType13},
    {".", OType14}
};

std::map<OperatorType, std::string> from_operator_to_str = {
    {OType1, "+"},
    {OType2, "-"},
    {OType3, "*"},
    {OType4, "/"},
    {OType5, "mod"},
    {OType6, "div"},
    {OType7, "="},
    {OType8, ":="},
    {OType9, ":"},
    {OType10, ";"},
    {OType11, ","},
    {OType12, "("},
    {OType13, ")"},
    {OType14, "."}
};

std::map<std::string, KeyWordType> from_str_to_kw = {
    {"program", Program},
    {"var", Var},
    {"if", If},
    {"then", Then},
    {"else", Else},
    {"for", For},
    {"while", While},
    {"do", Do},
    {"begin", Begin},
    {"end", End},
    {"read", Read},
    {"write", Write},
    {"integer", Integer},
    {"float", Float},
    {"readln", Readln},
    {"writeln", Writeln}
};

std::map<KeyWordType, std::string> from_kw_to_str = {
    {Program, "program"},
    {Var, "var"},
    {If, "if"},
    {Then, "then"},
    {Else, "else"},
    {For, "for"},
    {While, "while"},
    {Do, "do"},
    {Begin, "begin"},
    {End, "end"},
    {Read, "read"},
    {Write, "write"},
    {Integer, "integer"},
    {Float, "float"},
    {Readln, "readln"},
    {Writeln, "writeln"}
};


std::string make_low(std::string a){
    std::transform(a.begin(), a.end(), a.begin(), [](unsigned char c){ return std::tolower(c); });
    return a;
}

CToken::CToken(){
    TextPos help;
    pos.char_number = help.char_number;
    pos.line_number = help.line_number;
    tt = Constant;
}

CConstToken::CConstToken(TextPos position, std::string lexem){
    tt = Constant;
    pos = position;
    int x1;
    try {
        x1 = stoi(lexem);
        value = std::make_unique<CIntVariant>(x1);
        return;
    }
    catch(std::invalid_argument& e){ }
    float x2;
    try {
        x2 = stof(lexem);
        value = std::make_unique<CFloatVariant>(x2);
        return;
    }
    catch(std::invalid_argument& e){ }

    std::string help = make_low(lexem);
    if(help=="true" || help=="false"){
        bool what = help=="true";
        value = std::make_unique<CBoolVariant>(what);
    }
    else
        value = std::make_unique<CStringVariant>(lexem);
}

std::string CConstToken::ToString(){
    return value->ToString();
}

CIdentToken::CIdentToken(TextPos position, std::string lexem){
    tt = Identifier;
    pos = position;
    value = lexem;
}
std::string CIdentToken::ToString(){
    return value;
}

CKeyWordToken::CKeyWordToken(TextPos position, std::string lexem){
    tt = KeyWord;
    pos = position;
    value = from_str_to_kw[make_low(lexem)];
}

std::string CKeyWordToken::ToString(){
    return from_kw_to_str[value];
}

COperatorToken::COperatorToken(TextPos position, std::string lexem){
    tt = Operator;
    pos = position;
    value = from_str_to_operator[make_low(lexem)];
}

std::string COperatorToken::ToString(){
    return from_operator_to_str[value];
}

CVariant::CVariant(){
    vt = StringType;
}

CIntVariant::CIntVariant(int source){
    this->source = source;
    vt = IntegerType;
}

std::string CIntVariant::ToString(){
    return std::to_string(source);
}

CFloatVariant::CFloatVariant(float source){
    this->source = source;
    vt = FloatType;
}

std::string CFloatVariant::ToString(){
    return std::to_string(source);
}

CStringVariant::CStringVariant(std::string source){
    this->source = source;
    vt = StringType;
}

std::string CStringVariant::ToString(){
    return source;
}
CBoolVariant::CBoolVariant(bool source){
    this->source = source;
    vt = BoolType;
}

std::string CBoolVariant::ToString(){
    return source ? "true" : "false";
}