#include "pch.h"
#include "lexer_classes.h"

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
    {".", OType14},
    {"<>", OType15},
    {"<", OType16},
    {">", OType17},
    {"<=", OType18},
    {">=", OType19},
    {"or", OType20},
    {"and", OType21},
    {"not", OType22}
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
    {OType14, "."},
    {OType15, "<>"},
    {OType16, "<"},
    {OType17, ">"},
    {OType18, "<="},
    {OType19, ">="},
    {OType20, "or"},
    {OType21, "and"},
    {OType22, "not"}
};

std::map<std::string, KeyWordType> from_str_to_kw = {
    {"program", ProgramKW},
    {"var", VarKW},
    {"if", IfKW},
    {"const", ConstKW},
    {"then", ThenKW},
    {"else", ElseKW},
    {"for", ForKW},
    {"while", WhileKW},
    {"do", DoKW},
    {"begin", BeginKW},
    {"end", EndKW},
    {"read", ReadKW},
    {"write", WriteKW},
    {"integer", IntegerKW},
    {"real", FloatKW},
    {"string", StringKW},
    {"bool", BoolKW},
    {"readln", ReadlnKW},
    {"writeln", WritelnKW}
};

std::map<KeyWordType, std::string> from_kw_to_str = {
    {ProgramKW, "program"},
    {VarKW, "var"},
    {IfKW, "if"},
    {ConstKW, "const"},
    {ThenKW, "then"},
    {ElseKW, "else"},
    {ForKW, "for"},
    {WhileKW, "while"},
    {DoKW, "do"},
    {BeginKW, "begin"},
    {EndKW, "end"},
    {ReadKW, "read"},
    {WriteKW, "write"},
    {IntegerKW, "integer"},
    {FloatKW, "real"},
    {StringKW, "string"},
    {BoolKW, "bool"},
    {ReadlnKW, "readln"},
    {WritelnKW, "writeln"}
};

std::string make_low(std::string a) {
    std::transform(a.begin(), a.end(), a.begin(), [](unsigned char c) { return std::tolower(c); });
    return a;
}

bool can_cast(VarType from, VarType to) {
    return to == DefaultType || from == to || from == IntegerType && to == FloatType
        || from == BoolType && to != StringType;
}

CToken::CToken() {
    TextPos help;
    pos.char_number = help.char_number;
    pos.line_number = help.line_number;
    // tt = Constant;
}

CToken::CToken(TokenTp tt, TextPos pos) {
    this->tt = tt;
    this->pos = pos;
}

CConstToken::CConstToken() : CConstToken("") { }

CConstToken::CConstToken(std::string lexem) : CConstToken(TextPos(), lexem) { }

CConstToken::CConstToken(TextPos position, std::string lexem) : CToken(Constant, position){
    tt = Constant;
    pos = position;
    int cnt_c = 0, cnt_p = 0;
    bool is_num = lexem[0] >= '0' && lexem[0] <= '9';
    for (auto symb : lexem) {
        if (symb >= '0' && symb <= '9')
            cnt_c++;
        else if (symb == '.')
            cnt_p++;
    }
    if (cnt_p == 0 && is_num && cnt_c == lexem.length()) {
        value = std::make_unique<CIntVariant>(stoi(lexem));
        return;
    }
    else if (cnt_p == 1 && is_num && cnt_c == lexem.length() - 1) {
        value = std::make_unique<CFloatVariant>(stof(lexem));
        return;
    }
    std::string help = make_low(lexem);
    if (help == "true" || help == "false") {
        value = std::make_unique<CBoolVariant>(help == "true");
    }
    else
        value = std::make_unique<CStringVariant>(lexem);
}

std::string CConstToken::ToString() {
    return value->ToString();
}

CIdentToken::CIdentToken() : CIdentToken(TextPos(), "") { }

CIdentToken::CIdentToken(std::string lexem) : CIdentToken(TextPos(), lexem) { }

CIdentToken::CIdentToken(TextPos position, std::string lexem) : CToken(Identifier, position) {
    tt = Identifier;
    pos = position;
    value = lexem;
}

std::string CIdentToken::ToString() {
    return value;
}

CKeyWordToken::CKeyWordToken(std::string lexem) : CKeyWordToken(TextPos(), lexem) { }

CKeyWordToken::CKeyWordToken(TextPos position, std::string lexem) : CToken(KeyWord, position){
    tt = KeyWord;
    pos = position;
    value = from_str_to_kw[make_low(lexem)];
}

std::string CKeyWordToken::ToString() {
    return from_kw_to_str[value];
}

COperatorToken::COperatorToken() : COperatorToken("") { }

COperatorToken::COperatorToken(std::string lexem) : COperatorToken(TextPos(), lexem) {  }

COperatorToken::COperatorToken(TextPos position, std::string lexem) : CToken(Operator, position) {
    tt = Operator;
    pos = position;
    value = from_str_to_operator[make_low(lexem)];
}

std::string COperatorToken::ToString() {
    return from_operator_to_str[value];
}

CVariant::CVariant() {
    vt = StringType;
}

CVariant::CVariant(VarType vt) {
    this->vt = vt;
}

CIntVariant::CIntVariant(int source) : CVariant(IntegerType) {
    this->source = source;
    vt = IntegerType;
}

std::string CIntVariant::ToString() {
    return std::to_string(source);
}

CFloatVariant::CFloatVariant(float source) : CVariant(FloatType) {
    this->source = source;
    vt = FloatType;
}

std::string CFloatVariant::ToString() {
    return std::to_string(source);
}

CStringVariant::CStringVariant(std::string source) : CVariant(StringType) {
    this->source = source;
    vt = StringType;
}

std::string CStringVariant::ToString() {
    return source;
}
CBoolVariant::CBoolVariant(bool source) : CVariant(BoolType) {
    this->source = source;
    vt = BoolType;
}

std::string CBoolVariant::ToString() {
    return source ? "true" : "false";
}